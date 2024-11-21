#ifndef PRIVSPHERE_BERT_H__
#define PRIVSPHERE_BERT_H__

#include "layer.h"
#include "bert-config.h"

class Attention : public Layer {
    vector<vector<vector<uint64_t>>> wq, wk, wv;
    vector<vector<uint64_t>> bq, bk, bv;

    Linear* linear;
    SoftMax* softmax;
public:
    Attention();
    ~Attention();

    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output);
};

class FFN : public Layer {
    vector<vector<vector<uint64_t>>> w1, w2;
    vector<vector<uint64_t>> b1, b2;

    Linear *linear;
    GeLU *gelu;
public:
    FFN();
    ~FFN();

    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output);
};

class Encoder : public Layer {
    Attention *attention;
    LayerNorm *ln1;
    FFN *ffn;
    LayerNorm *ln2;

public:
    Encoder();
    ~Encoder();
    
    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output);
};

class Bert : public Layer {
    Encoder **encoder;

public:
    static const unsigned int num_layers = 12;
    Bert();
    ~Bert();

    void forward(const vector<vector<vector<uint64_t>>> &input, vector<vector<vector<uint64_t>>> &output);
};

#endif