#include "protocols.h"
#include "FloatingPoint/fixed-point.h"

void convert(unsigned party, const MPCType s, const MPCType t, const Data& i, Data& o) {
    o = Data();
    switch (s) {
    case MPCType::HE:
        switch (t) {
        case MPCType::HE:
            o.HEData = i.HEData;
            return;
        case MPCType::SS:
            return;
        case MPCType::NEXUS:
            o.NexusData = vector<vector<vector<double>>>(
                i.HEData.size(),
                vector<vector<double>>(i.HEData[0].size(),
                                       vector<double>(i.HEData[0][0].size(), 0.0)));
            return;
        }
        return;
    case MPCType::SS:
        switch (t) {
        case MPCType::HE:
            return;
        case MPCType::SS:
            o.SSData = i.SSData;
            return;
        case MPCType::NEXUS:
            return;
        }
        return;
    case MPCType::NEXUS:
        switch (t) {
        case MPCType::HE:
            o.HEData = vector<vector<vector<uint64_t>>>(
                i.NexusData.size(),
                vector<vector<uint64_t>>(i.NexusData[0].size(),
                                         vector<uint64_t>(i.NexusData[0][0].size(), 0)));
            return;
        case MPCType::SS:
            return;
        case MPCType::NEXUS:
            o.NexusData = i.NexusData;
            return;
        }
        return;
    }
}

void load_data(vector<vector<vector<uint64_t>>>& A, size_t dim1, size_t dim2, size_t dim3) {
    A = vector<vector<vector<uint64_t>>>(dim1,
                                         vector<vector<uint64_t>>(dim2, vector<uint64_t>(dim3, 1)));
}

void load_data(vector<vector<uint64_t>>& B, size_t dim1, size_t dim2) {
    B = vector<vector<uint64_t>>(dim1, vector<uint64_t>(dim2, 1));
}

Ciphertext SS2HE(FixArray ss_data, NetIO* io, Encryptor* encryptor, CKKSEncoder* encoder,
                 Evaluator* evaluator, SEALContext* context, double scale) {
    assert(encoder != nullptr);
    Ciphertext ct;
    Plaintext pt;
    vector<double> data = ss_data.get_native_type<double>();
    encoder->encode(data, scale, pt);
    if (encryptor != nullptr) {
        encryptor->encrypt(pt, ct);
        // send to other
        send_ct(io, &ct);
    } else {
        assert(evaluator != nullptr);
        assert(context != nullptr);
        // recv from other
        recv_ct(io, &ct, context);
        evaluator->add_plain_inplace(ct, pt);
    }
    return ct;
}

FixArray HE2SS(int party, Ciphertext& ct, NetIO* io, Decryptor* decryptor, CKKSEncoder* encoder,
               Evaluator* evaluator, SEALContext* context, double scale) {
    Plaintext pt;
    vector<double> data;
    if (decryptor != nullptr) {
        Ciphertext ct_rev;
        recv_ct(io, &ct_rev, context);
        decryptor->decrypt(ct_rev, pt);
        encoder->decode(pt, data);
    } else {
        Ciphertext ct_send;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(-1, 1);
        for (int i = 0; i < ct.size(); i++) {
            data.push_back(dist(gen));
        }
        encoder->encode(data, scale, pt);
        evaluator->sub_plain(ct, pt, ct_send);
        send_ct(io, &ct_send);
    }
    size_t size = data.size();
    FixArray ret(party, size, true, ELL, SCALE);
    for (int i = 0; i < size; i++) {
        uint64_t fix_data = static_cast<uint64_t>(data[i] * (1ULL << SCALE));
        ret.data[i] = neg_mod(fix_data, (int64_t)(1ULL << ELL));
    }
    return ret;
}