#include "bert.h"

#include <cmath>
#include <cstdint>

#include "layer.h"

Attention::Attention() {
    linear  = new Linear();
    softmax = new SoftMax();
}

Attention::~Attention() {
    delete linear;
    delete softmax;
}

void Attention::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    const unsigned int num_features = input.size();
    const double scale              = 1.0 / sqrt(dk);

    vector<vector<vector<uint64_t>>> Q(num_features, vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> K(num_features, vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> V(num_features, vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(dk)));
    vector<vector<vector<uint64_t>>> Kt(num_features, vector<vector<uint64_t>>(dk, vector<uint64_t>(BATCH_SIZE)));

    linear->forward(input, wq, Q);
    linear->forward(input, wk, K);
    linear->forward(input, wv, V);

    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < BATCH_SIZE; j++) {
            for (unsigned k = 0; k < dk; k++) {
                Q[i][j][k] += bq[i][j];
                K[i][j][k] += bk[i][j];
                V[i][j][k] += bv[i][j];
            }
        }
    }
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < BATCH_SIZE; j++) {
            for (unsigned k = 0; k < dk; k++) {
                Kt[i][k][j] = K[i][j][k];
            }
        }
    }

    vector<vector<vector<uint64_t>>> QK(num_features,
                                        vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(BATCH_SIZE)));
    linear->forward(Q, Kt, QK);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < BATCH_SIZE; j++) {
            for (unsigned k = 0; k < BATCH_SIZE; k++) {
                QK[i][j][k] = static_cast<uint64_t>(QK[i][j][k] * scale);
            }
        }
    }

    softmax->forward(QK, QK);
    linear->forward(QK, V, output);
}

MultiHeadAttention::MultiHeadAttention() {
    attns = new Attention*[N_HEADS];
    for (int i = 0; i < N_HEADS; i++) {
        attns[i] = new Attention();
    }
}

MultiHeadAttention::~MultiHeadAttention() {
    for (int i = 0; i < N_HEADS; i++) {
        delete attns[i];
    }
    delete[] attns;
}

void MultiHeadAttention::forward(const vector<vector<vector<uint64_t>>>& input,
                                 vector<vector<vector<uint64_t>>>& output) {
    const unsigned int num_features = input.size();
    vector<vector<vector<uint64_t>>> attns_output(N_HEADS,
                                                  vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(SEQ_LEN)));

    for (int h = 0; h < N_HEADS; h++) {
        vector<vector<vector<uint64_t>>> output_h(num_features,
                                                  vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(SEQ_LEN)));
        attns[h]->forward(input, output_h);
        for (unsigned int f = 0; f < num_features; f++) {
            for (unsigned int i = 0; i < BATCH_SIZE; i++) {
                for (unsigned int j = 0; j < dk; j++) {
                    attns_output[f][i * SEQ_LEN + h * dk + j] = output_h[f][i * dk + j];
                }
            }
        }
    }
}

FFN::FFN() {
    linear = new Linear();
    gelu   = new GeLU();
}

FFN::~FFN() {
    delete linear;
    delete gelu;
}

void FFN::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    const unsigned int num_features = input.size();
    vector<vector<vector<uint64_t>>> h1(num_features, vector<vector<uint64_t>>(BATCH_SIZE, vector<uint64_t>(FFN_DIM)));

    linear->forward(input, w1, h1);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < BATCH_SIZE; j++) {
            for (unsigned k = 0; k < FFN_DIM; k++) {
                h1[i][j][k] += b1[i][j];
            }
        }
    }

    gelu->forward(h1, h1);

    linear->forward(h1, w2, output);
    for (unsigned i = 0; i < num_features; i++) {
        for (unsigned j = 0; j < BATCH_SIZE; j++) {
            for (unsigned k = 0; k < SEQ_LEN; k++) {
                output[i][j][k] += b2[i][j];
            }
        }
    }
}

Encoder::Encoder() {
    attention = new MultiHeadAttention();
    ln1       = new LayerNorm();
    ffn       = new FFN();
    ln2       = new LayerNorm();
}

Encoder::~Encoder() {
    delete attention;
    delete ln1;
    delete ffn;
    delete ln2;
}

void Encoder::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    attention->forward(input, output);
    ln1->forward(output, output);
    ffn->forward(output, output);
    ln2->forward(output, output);
}

Bert::Bert() {
    encoder = new Encoder*[N_LAYERS];
    for (unsigned int i = 0; i < N_LAYERS; i++) {
        encoder[i] = new Encoder();
    }
}

Bert::~Bert() {
    for (unsigned int i = 0; i < N_LAYERS; i++) {
        delete encoder[i];
    }
    delete[] encoder;
}

void Bert::forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output) {
    encoder[0]->forward(input, output);
    for (unsigned int i = 1; i < N_LAYERS; i++) {
        encoder[i]->forward(output, output);
    }
}