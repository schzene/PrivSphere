#include "bert.h"
#include "layer.h"
#include <cmath>

Attention::Attention() {
    linear = new Linear();
    softmax = new SoftMax();
}

Attention::~Attention() {
    delete linear;
    delete softmax;
}

void Attention::forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {
    const unsigned int num_features = input.size(), batch_size = input[0].size(), seq_len = input[0][0].size(), dk = wq[0][0].size();
    const double scale = 1.0 / sqrt(dk);

    vector<vector<vector<uint64_t>>> Q(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> K(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> V(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> Vt(num_features, vector<vector<uint64_t>>(dk, vector<uint64_t>(batch_size)));

    linear->forward(input, wq, Q);
    linear->forward(input, wk, K);
    linear->forward(input, wv, V);

    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < batch_size; j++) {
            for (unsigned k = 0; k < dk; k++) {
                Q[i][j][k] += bq[i][j];
                K[i][j][k] += bk[i][j];
                V[i][j][k] += bv[i][j];
            }
        }
    }
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < batch_size; j++) {
            for (unsigned k = 0; k < dk; k++) {
                Vt[i][k][j] = V[i][j][k];
            }
        }
    }

    vector<vector<vector<uint64_t>>> QK(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(batch_size)));
    linear->forward(Q, K, QK);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < batch_size; j++) {
            for (unsigned k = 0; k < batch_size; k++) {
                QK[i][j][k] = static_cast<uint64_t>(QK[i][j][k] * scale);
            }
        }
    }

    softmax->forward(QK, QK);
    linear->forward(QK, Vt, output);
}

FFN::FFN() {
    linear = new Linear();
    gelu = new GeLU();
}

FFN::~FFN() {
    delete linear;
    delete gelu;
}

void FFN::forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {
    const unsigned int num_features = input.size(), batch_size = input[0].size(), seq_len = input[0][0].size(), dim1 = w1[0][0].size(), dim2 = w2[0][0].size();
    vector<vector<vector<uint64_t>>> h1(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(dim1)));
    vector<vector<vector<uint64_t>>> h2(num_features, vector<vector<uint64_t>>(batch_size, vector<uint64_t>(dim2)));

    linear->forward(input, w1, h1);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < batch_size; j++) {
            for (unsigned k = 0; k < dim1; k++) {
                h1[i][j][k] = h1[i][j][k] + b1[i][j];
            }
        }
    }

    gelu->forward(h1, h1);

    linear->forward(h1, w2, h2);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < batch_size; j++) {
            for (unsigned k = 0; k < dim2; k++) {
                output[i][j][k] = h2[i][j][k] + b2[i][j];
            }
        }
    }
}

Encoder::Encoder() {
    attention = new Attention();
    ln1 = new LayerNorm();
    ffn = new FFN();
    ln2 = new LayerNorm();
}

Encoder::~Encoder() {
    delete attention;
    delete ln1;
    delete ffn;
    delete ln2;
}

void Encoder::forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {
    attention->forward(input, output);
    ln1->forward(output, output);
    ffn->forward(output, output);
    ln2->forward(output, output);
}

Bert::Bert() {
    encoder = new Encoder*[num_layers];
    for (unsigned int i = 0; i < num_layers; i++) {
        encoder[i] = new Encoder();
    }
}

Bert::~Bert() {
    for (unsigned int i = 0; i < num_layers; i++) {
        delete encoder[i];
    }
    delete[] encoder;
}

void Bert::forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output) {
    encoder[0]->forward(input, output);
    for (unsigned int i = 1; i < num_layers; i++) {
        encoder[i]->forward(output, output);
    }
}