#pragma once

#include <seal/seal.h>

#include <vector>

#include "ckks_evaluator.h"

namespace nexus {
class MMEvaluator {
 private:
  CKKSEvaluator *ckks = nullptr;

  void enc_compress_ciphertext(vector<double> &vec, Ciphertext &ct);
  void multiply_power_of_x(Ciphertext &encrypted, Ciphertext &destination, int index);
  vector<Ciphertext> expand_ciphertext(const Ciphertext &encrypted, uint32_t m, GaloisKeys &galkey, vector<uint32_t> &galois_elts);

 public:
  MMEvaluator(CKKSEvaluator &ckks) {
    this->ckks = &ckks;
  }

/**
  只能用于固定大小的矩阵乘法，
  即（128×768）×（768×64）的矩阵乘法
  👎🖕
 */
  void matrix_mul(vector<vector<double>> &x, vector<vector<double>> &y, vector<Ciphertext> &res);

  std::vector<std::vector<double>> readMatrix(const std::string &filename, int rows, int cols);
  std::vector<std::vector<double>> transposeMatrix(const std::vector<std::vector<double>> &matrix);
};
}