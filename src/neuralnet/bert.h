#pragma once
#ifndef PRIVSPHERE_BERT_H__
#define PRIVSPHERE_BERT_H__

#include <string>

#include "bert-config.h"
#include "layer.h"

#define BATCH_SIZE 128
#define SEQ_LEN    768
#define N_HEADS    12
#define N_LAYERS   12
#define FFN_DIM    3072

const int dk = SEQ_LEN / N_HEADS;

#include "../protocols/protocols.h"
using std::string;
const string data_folder = "/data/";

class Attention : public Layer {
    unsigned int party;
    unsigned int n;
    vector<vector<vector<uint64_t>>> wq, wk, wv;
    vector<vector<uint64_t>> bq, bk, bv;

    Linear* linear;
    SoftMax* softmax;

public:
    Attention(unsigned party, unsigned int n);
    ~Attention();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class MultiHeadAttention : public Layer {
    unsigned int party;
    unsigned int n;
    Attention** attns;

public:
    MultiHeadAttention(unsigned int party, unsigned int n);
    ~MultiHeadAttention();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class FFN : public Layer {
    unsigned int party;
    unsigned int n;
    vector<vector<vector<uint64_t>>> w1, w2;
    vector<vector<uint64_t>> b1, b2;

    Linear* linear;
    GeLU* gelu;

public:
    FFN(unsigned int party, unsigned int n);
    ~FFN();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class Encoder : public Layer {
    unsigned int party;
    unsigned int n;
    MultiHeadAttention* attention;
    LayerNorm* ln1;
    FFN* ffn;
    LayerNorm* ln2;

public:
    Encoder(unsigned int party, unsigned int n);
    ~Encoder();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

class Bert : public Layer {
    unsigned int party;
    Encoder** encoder;

public:
    Bert(unsigned int party);
    ~Bert();

    void forward(const vector<vector<vector<uint64_t>>>& input, vector<vector<vector<uint64_t>>>& output);
};

#endif