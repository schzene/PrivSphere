#ifndef FIELD_DATA_H_
#define FIELD_DATA_H_

#include <immintrin.h>

#include <Eigen/Core>
#include <iostream>

#include "emp-tool.h"  // add const:PUBLIC ALICE BOB

#define PR_31
using Eigen::MatrixBase, Eigen::RowMajor;
using std::istream;
using std::ostream;

namespace nisl {

#if defined(PR_31) && !defined(PR_61)
using TYPE  = unsigned int;  //{unsigned int, uint64_t}
using DTYPE = uint64_t;      //{uint64_t, __uint128_t}
using STYPE = int;           //{int, int64_t}
using u64   = uint64_t;
// {31, 61, 127}
const int MERSENNE_PRIME_EXP = 31;
const int PRIME_LENGTH       = MERSENNE_PRIME_EXP;
const static TYPE PR         = 2147483647;
const static DTYPE pr        = 2147483647;

const static TYPE RSQRT_CONST = 1610612734;  // rsqrt = x^{RSQRT_CONST} = 1/sqrt(x)

// Bit
const static size_t BITS_LENGTH     = 31;  // {31, 61}
const static size_t n_BITS_LENGTH   = 5;   // {5, 6}6 = log(61)+1
const static size_t FIXED_PRECISION = 12;  // 11 bits for fixed point part

const static TYPE ConstTwoInverse = 1073741824;

#elif defined(PR_61) && !defined(PR_31)
using TYPE                   = uint64_t;     //{unsigned int, uint64_t}
using DTYPE                  = __uint128_t;  //{uint64_t, __uint128_t}
using STYPE                  = int64_t;      //{int, int64_t}
using u64                    = uint64_t;
const int MERSENNE_PRIME_EXP = 61;
const int PRIME_LENGTH       = MERSENNE_PRIME_EXP;
const static TYPE PR         = 2305843009213693951;
const static DTYPE pr        = 2305843009213693951;

const static TYPE RSQRT_CONST = 1729382256910270462;  // rsqrt = x^{RSQRT_CONST} = 1/sqrt(x)

// Bit
const static size_t BITS_LENGTH     = 61;  // {31, 61}
const static size_t n_BITS_LENGTH   = 6;   // {5, 6}6 = log(61)+1
const static size_t FIXED_PRECISION = 13;  // 21 bits for fixed point part

const static TYPE ConstTwoInverse = 1152921504606846976;
#endif

static PRG128 prg;
const static TYPE MID_PR = ((PR - 1) >> 1) + 1;  // Middle point

const static TYPE SQRT_EXP      = (PR + 1) >> 2;  // sqrt(x) = x^{SQRT_EXP}
const static TYPE INVERSE_CONST = PR - 2;         // inv = x^{PR-2}

const static size_t INT_PRECISION = BITS_LENGTH - FIXED_PRECISION;  // 40 bits for integer part
const static TYPE MAX_POSITIVE    = PR >> 1;

const static TYPE ConstGapInTruncation = ((TYPE)1 << INT_PRECISION) - 1;
const static TYPE ConstEncode          = (TYPE)1 << (BITS_LENGTH - 2);
const static TYPE ConstDecode          = (TYPE)1 << (BITS_LENGTH - 2 - FIXED_PRECISION);

template <typename T>
T additive_inverse(const T x);
template <typename T>
T multiplicative_inverse(const T x);
template <typename T>
bool test_inverse(T a, T b);
template <typename T>
T add_mod(T a, T b);
template <typename T>
T mult_mod(T a, T b);
template <typename T>
T modPrime(T x);
template <typename T>
void extend_gcd(const T, const T, T& x, T& y);
class gfpScalar;
template <typename T>
using eMatrix   = Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using gfpMatrix = Eigen::Matrix<gfpScalar, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>;
using gfpVector = Eigen::Matrix<gfpScalar, Eigen::Dynamic, 1>;

class gfpScalar {
    // Operations between gfpScalars
    friend istream& operator>>(istream& is, gfpScalar& it);
    friend ostream& operator<<(ostream& os, const gfpScalar& it);
    friend bool operator<(const gfpScalar& a, const gfpScalar& b);
    friend bool operator==(const gfpScalar& a, const gfpScalar& b);
    friend bool operator!=(const gfpScalar& a, const gfpScalar& b);
    friend bool operator<=(const gfpScalar& a, const gfpScalar& b);
    friend bool operator>(const gfpScalar& a, const gfpScalar& b);
    friend bool operator>=(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator+(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator-(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator*(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator/(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator&(const gfpScalar& a, const gfpScalar& b);
    friend gfpScalar operator<<(const gfpScalar& a, const gfpScalar& x);  // left shift bits
    friend gfpScalar operator>>(const gfpScalar& a, const gfpScalar& x);

    friend gfpScalar sqrt(const gfpScalar& x);
    friend gfpScalar rsqrt(const gfpScalar& x);
    friend gfpScalar square(const gfpScalar& x);
    template <typename T>
    friend gfpScalar pow(const gfpScalar& x, T exp);
    friend gfpScalar inverse(const gfpScalar& x);
    friend gfpScalar truncate(const gfpScalar& x, size_t d);

protected:
    TYPE value;

public:
    gfpScalar() = default;
    gfpScalar(TYPE _value) : value(_value) {}
    TYPE get_value() const {
        return value;
    }
    void set_value(TYPE& _v) {
        value = _v;
    }

    gfpScalar operator-() const;
    gfpScalar& operator+=(const gfpScalar& other);
    gfpScalar& operator-=(const gfpScalar& other);
    gfpScalar& operator*=(const gfpScalar& other);
    gfpScalar& operator/=(const gfpScalar& other);
    gfpScalar& operator&=(const gfpScalar& other);   // bitwise &
    gfpScalar& operator<<=(const gfpScalar& other);  // left shitf
    gfpScalar& operator>>=(const gfpScalar& other);  // right shift

    // Basic Math Methods
    gfpScalar& square();   // a^2
    gfpScalar& sqrt();     // sqrt(a)
    gfpScalar& inverse();  // 1/a
    gfpScalar& rsqrt();    // 1/sqrt(a)
    template <typename T>
    gfpScalar& pow(T exp); 

    // Get Bit

    // Random Methods
    void random();
    void random_bit();

    // For sint and sfix
    bool is_zero() const {
        return value == 0;
    }
    bool is_negative() const {
        return value > MAX_POSITIVE;
    }
    gfpScalar& truncate(size_t d = FIXED_PRECISION);  // Right shift bits with sign bit.
    gfpScalar& magnify();                             // Left shift bits with sign bit
    gfpScalar msb() const {
        return (TYPE)is_negative();
    }
};

#if defined(__x86_64__) && defined(__BMI2__)
inline uint64_t mul64(uint64_t a, uint64_t b, uint64_t* c) {
    return _mulx_u64((unsigned long long)a, (unsigned long long)b, (unsigned long long*)c);
}
#else
inline uint64_t mul64(uint64_t a, uint64_t b, uint64_t* c) {
    __uint128_t aa = a;
    __uint128_t bb = b;
    auto cc        = aa * bb;
    *c             = cc >> 64;
    return (uint64_t)cc;
}
#endif

// #if  defined(__BMI2__)
// inline unsigned int mul32(unsigned int a, unsigned int b, unsigned int *c)
// {
//     return _mulx_u32((unsigned int)a, (unsigned int)b, (unsigned int*)c);
// }
// #else
inline unsigned int mul32(unsigned int a, unsigned int b, unsigned int* c) {
    uint64_t aa = a;
    uint64_t bb = b;
    auto cc     = aa * bb;
    *c          = cc >> 32;
    return (unsigned int)cc;
}
// #endif

template <typename T>
inline T add_mod(T a, T b) {
    T ret = a + b;
    return (ret >= PR) ? (ret - PR) : ret;
}

template <typename T>
inline T mult_mod(T a, T b) {
    T c = 0;
    T e, ret;
#if defined(PR_31)
    e   = mul32((unsigned int)a, (unsigned int)b, (unsigned int*)&c);
    ret = (e & PR) + ((e >> MERSENNE_PRIME_EXP) ^ ((T)c << (32 - MERSENNE_PRIME_EXP)));
#elif defined(PR_61)
    e   = mul64((uint64_t)a, (uint64_t)b, (uint64_t*)&c);
    ret = (e & PR) + ((e >> MERSENNE_PRIME_EXP) ^ (c << (64 - MERSENNE_PRIME_EXP)));
#endif
    // c is most significant bits
    // e is low significant bits
    return (ret >= PR) ? (ret - PR) : ret;
}

template <typename T>
inline T modPrime(T x) {
    T i = (x & PR) + (x >> MERSENNE_PRIME_EXP);
    return (i >= PR) ? i - PR : i;
}

template <typename T>
inline void extend_gcd(const T a, const T b, T& x, T& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    extend_gcd(b, a % b, y, x);
    // a/b * x  execeed TYPE
    T tmp = mult_mod((T)(a / b), x);
    y     = add_mod(y, additive_inverse(tmp));
    return;
}

template <typename T>
inline T additive_inverse(const T x) {
    if (x == 0) {
        return 0;
    }  // BUG LOG
    return PR ^ x;
}

template <typename T>
inline T multiplicative_inverse(const T it) {
    T x, y;
    extend_gcd((const T)PR, (const T)it, x, y);
    return y;
}

template <typename T>
inline bool test_inverse(T a, T b) {
    return mult_mod(a, b) == 1;
}

inline istream& operator>>(istream& is, gfpScalar& it) {
    is >> it.value;
    return is;
}

inline ostream& operator<<(ostream& os, const gfpScalar& it) {
    os << it.value;
    return os;
}

inline gfpScalar operator+(const gfpScalar& a, const gfpScalar& b) {
    return gfpScalar(add_mod(a.value, b.value));
}

inline gfpScalar gfpScalar::operator-() const {
    return gfpScalar(additive_inverse(value));
}

inline gfpScalar& gfpScalar::operator+=(const gfpScalar& other) {
    value = add_mod(value, other.value);
    return *this;
}

inline gfpScalar operator-(const gfpScalar& a, const gfpScalar& b) {
    return gfpScalar(add_mod(a.value, additive_inverse(b.value)));
}

inline gfpScalar& gfpScalar::operator-=(const gfpScalar& other) {
    value = add_mod(value, additive_inverse(other.value));
    return *this;
}

inline gfpScalar operator*(const gfpScalar& a, const gfpScalar& b) {
    return gfpScalar(mult_mod(a.value, b.value));
}

inline gfpScalar& gfpScalar::operator*=(const gfpScalar& other) {
    value = mult_mod(value, other.value);
    return *this;
}

inline gfpScalar operator/(const gfpScalar& a, const gfpScalar& b) {
    return gfpScalar(mult_mod(a.value, multiplicative_inverse(b.value)));
}

inline gfpScalar& gfpScalar::operator/=(const gfpScalar& other) {
    value = mult_mod(value, multiplicative_inverse(other.value));
    return *this;
}

inline bool operator==(const gfpScalar& a, const gfpScalar& b) {
    return a.value == b.value;
}

inline bool operator!=(const gfpScalar& a, const gfpScalar& b) {
    return a.value != b.value;
}

inline bool operator<(const gfpScalar& a, const gfpScalar& b) {
    return a.value < b.value;
}

inline bool operator<=(const gfpScalar& a, const gfpScalar& b) {
    return (a.value < b.value) || (a.value == b.value);
}

inline bool operator>(const gfpScalar& a, const gfpScalar& b) {
    return (a.value > b.value);
}

inline bool operator>=(const gfpScalar& a, const gfpScalar& b) {
    return !(a.value < b.value);
}

/*************************************************
 * 
 *       Basic Math Methods
 * 
 * ***********************************************/
inline gfpScalar& gfpScalar::square() {
    value = mult_mod(value, value);
    return *this;
}

inline gfpScalar square(const gfpScalar& x) {
    return gfpScalar(mult_mod(x.value, x.value));
}

template <typename T>
inline gfpScalar& gfpScalar::pow(T exp) {
    gfpScalar res(1);
    gfpScalar v_pow = *this;
    while (exp) {
        if (exp & 1) {
            res *= v_pow;
        }
        exp >>= 1;
        v_pow.square();
    }
    value = res.value;
    return *this;
}

template <typename T>
inline gfpScalar pow(const gfpScalar& x, T exp) {
    gfpScalar res(1);
    gfpScalar v_pow = x;
    while (exp) {
        if (exp & 1) {
            res *= v_pow;
        }
        exp >>= 1;
        v_pow.square();
    }
    return res;
}

inline gfpScalar& gfpScalar::sqrt() {
    assert(value > 0);
    pow((TYPE)SQRT_EXP);
    if (value >= 1 && value < MID_PR) {
        return *this;
    }
    else {
        value = additive_inverse(value);
        return *this;
    }
}

inline gfpScalar sqrt(const gfpScalar& x) {
    assert(x.value > 0);
    gfpScalar res = pow(x, (TYPE)SQRT_EXP);
    if (res.value >= 1 && res.value < MID_PR) {
        return res;
    }
    else {
        return -res;
    }
}

// BUG LOG: Need to invoke sqrt to ensure the rang is [1, (p-1)/2]
inline gfpScalar& gfpScalar::rsqrt() {
    if (value == 0) {
        return *this;
    }  // For simplicity.

    sqrt();
    inverse();

    // pow((TYPE)RSQRT_CONST); // TODO: We can(?) calculate rsqrt in one pow.
    return *this;
}

inline gfpScalar rsqrt(const gfpScalar& x) {
    if (x.value == 0) {
        return x;
    }  // For simplicity.

    gfpScalar res = x;
    res.sqrt();
    res.inverse();
    return res;
    // return pow(x, RSQRT_CONST);
}

inline gfpScalar& gfpScalar::inverse() {
    value = multiplicative_inverse(value);
    return *this;
}

inline gfpScalar operator&(const gfpScalar& a, const gfpScalar& b) {
    return gfpScalar(a.value & b.value);
}

inline gfpScalar& gfpScalar::operator&=(const gfpScalar& other) {
    value &= other.value;
    return *this;
}

inline gfpScalar operator<<(const gfpScalar& a, const gfpScalar& x) {
    return gfpScalar(a.value << x.value);
}

inline gfpScalar operator>>(const gfpScalar& a, const gfpScalar& x) {
    return gfpScalar(a.value >> x.value);
}

inline gfpScalar& gfpScalar::operator<<=(const gfpScalar& other) {
    value <<= other.value;
    return *this;
}

inline gfpScalar& gfpScalar::operator>>=(const gfpScalar& other) {
    value >>= other.value;
    return *this;
}
/*************************************************
 * 
 *       Custom Methods

 * ***********************************************/
inline void gfpScalar::random() {
#if defined(PR_31)
    prg.random_data(&value, 31);
    value = modPrime(value);
#elif defined(PR_61)
    prg.random_data(&value, 64);
    value = modPrime(value);
#endif
}

inline void gfpScalar::random_bit() {
    prg.random_data(&value, 8);
}

// Truncate d bits if there is a sign bit.
inline gfpScalar& gfpScalar::truncate(size_t d) {
    if (is_negative()) {
        value = additive_inverse(value);
        value >>= d;
        value = additive_inverse(value);
    }
    else {
        value >>= d;
    }
    return *this;
}

inline gfpScalar truncate(const gfpScalar& x, size_t d = FIXED_PRECISION) {
    gfpScalar res(x);
    return res.truncate(d);
}

inline gfpScalar& gfpScalar::magnify() {
    if (is_negative()) {
        value = additive_inverse(value);
        value <<= FIXED_PRECISION;
        value = additive_inverse(value);
    }
    else {
        value <<= FIXED_PRECISION;
    }
    return *this;
}

inline gfpScalar map_int_to_gfp(const STYPE& x) {
    if (x < 0) {
        return gfpScalar(x + (STYPE)PR);
    }
    return gfpScalar((TYPE)x);
}

inline STYPE map_gfp_to_int(const gfpScalar& x) {
    STYPE res = x.get_value();
    if (res > MAX_POSITIVE) {
        res -= (STYPE)PR;
    }
    return res;
}

const static TYPE FACTOR = 1 << FIXED_PRECISION;

inline gfpScalar map_float_to_gfp(const double& x) {
    return map_int_to_gfp((STYPE)floor(x * FACTOR));
}

inline double map_gfp_to_float(const gfpScalar& x) {
    return ((double)map_gfp_to_int(x)) / (float)FACTOR;
}

}

namespace Eigen {
template <>
struct NumTraits<nisl::gfpScalar> : NumTraits<unsigned int> {
    typedef nisl::gfpScalar Real;
    typedef nisl::gfpScalar NonInteger;
    typedef nisl::gfpScalar Nested;

    enum {
        IsComplex             = 0,
        IsInteger             = 1,
        IsSigned              = 1,
        RequireInitialization = 0,
        ReadCost              = 1,
        AddCost               = 3,
        MulCost               = 3,
    };
};
template <typename BinaryOp>
struct ScalarBinaryOpTraits<nisl::gfpScalar, nisl::TYPE, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};
template <typename BinaryOp>
struct ScalarBinaryOpTraits<nisl::TYPE, nisl::gfpScalar, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};

template <typename BinaryOp>
struct ScalarBinaryOpTraits<nisl::gfpScalar, int, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};
template <typename BinaryOp>
struct ScalarBinaryOpTraits<int, nisl::gfpScalar, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};

template <typename BinaryOp>
struct ScalarBinaryOpTraits<nisl::gfpScalar, int64_t, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};
template <typename BinaryOp>
struct ScalarBinaryOpTraits<int64_t, nisl::gfpScalar, BinaryOp> {
    typedef nisl::gfpScalar ReturnType;
};

}  // namespace Eigen

namespace nisl {
// using block = __m128i;

// #ifdef __x86_64__
// __attribute__((target("sse2")))
// inline block makeBlock(uint64_t high, uint64_t low) {
// 	return _mm_set_epi64x(high, low);
// }
// #elif __aarch64__
// inline block makeBlock(uint64_t high, uint64_t low) {
// 	return (block)vcombine_u64((uint64x1_t)low, (uint64x1_t)high);
// }
// #endif

// const static block prs = makeBlock(2305843009213693951ULL, 2305843009213693951ULL);

typedef Eigen::Matrix<TYPE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMatrixXi64;
typedef Eigen::Matrix<TYPE, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> ColMatrixXi64;
typedef Eigen::Matrix<TYPE, 1, Eigen::Dynamic, Eigen::RowMajor> RowVectorXi64;
typedef Eigen::Matrix<TYPE, Eigen::Dynamic, 1, Eigen::ColMajor> ColVectorXi64;
typedef Eigen::Matrix<STYPE, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> SignedRowMatrixXi64;
typedef Eigen::Matrix<STYPE, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> SignedColMatrixXi64;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> RowMatrixXd;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::ColMajor> ColMatrixXd;
typedef Eigen::Matrix<double, 1, Eigen::Dynamic, Eigen::RowMajor> RowVectorXd;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1, Eigen::ColMajor> ColVectorXd;
/**
 * @brief Mod the matrix using SIMD.
 * 
 * @tparam Derived 
 * @param matrix 
 */
// template<typename Derived>
// void mod_matrix(Eigen::PlainObjectBase<Derived> &matrix)
// {
//     block *ptr = (block*)matrix.data();
//     for(size_t i = 0; i < matrix.size()/2; i++){
//         // 2-64bit (x & PR) + (x >> MERSENNE_PRIME_EXP);
//         ptr[i] = _mm_add_epi64(((block)ptr[i] & prs), _mm_srli_epi64(ptr[i], MERSENNE_PRIME_EXP));
//         // 2-64bit (i >= pv) ? i - pv : i;
//         ptr[i] = _mm_sub_epi64(ptr[i], _mm_andnot_si128(_mm_cmpgt_epi64(prs,ptr[i]), prs));
//     }

//     if(matrix.size() % 2){
//         size_t id_last = matrix.size() - 1;
//         matrix(id_last) = modPrime(matrix(id_last).get_value());
//     }
// }

/**
 * @brief There are two ways to generate a random matrix.
 * One is to call the modPrime() on each entry of the matrix.
 * The other is to generate the random memory directly, and mod them.
 * TODO [Test] For now, the performance is close.
 * @tparam Derived 
 * @param matrix 
 */
template <typename Derived>
void random_matrix(Eigen::PlainObjectBase<Derived>& matrix) {
    // * The first way: Generate random element one by one
    for (size_t i = 0; i < matrix.size(); i++) {
#if defined(PR_31)
        prg.random_data(&matrix(i), 31);
        matrix(i) = modPrime(matrix(i));
#elif defined(PR_61)
        prg.random_data(&matrix(i), 64);
        matrix(i) = modPrime(matrix(i));
#endif
    }

    // * The second way
    // size_t len = matrix.size()*sizeof(gfpScalar);
    // const auto *ptr = matrix.data();
    // secure_prng.get_octets((octet*)ptr, len);
    // mod_matrix(matrix);
}

template <typename Derived>
void random_matrix(Eigen::PlainObjectBase<Derived>& matrix, PRG128& prg) {
    // * The first way: Generate random element one by one
    for (size_t i = 0; i < matrix.size(); i++) {
#if defined(PR_31)
        prg.random_data(&matrix(i), 31);
        matrix(i) = modPrime(matrix(i));
#elif defined(PR_61)
        prg.random_data(&matrix(i), 64);
        matrix(i) = modPrime(matrix(i));
#endif
    }
}

/**
 * @brief Truncate each entry in the matrix.
 * 
 * @tparam Derived 
 * @param matrix 
 */
template <typename Derived>
void truncate_matrix(Eigen::MatrixBase<Derived>& matrix, size_t precision = FIXED_PRECISION) {
    for (size_t i = 0; i < matrix.size(); i++) {
        matrix(i).truncate(precision);
    }
}

/**
 * @brief Pack the matrix.row(i) into the octetStream os(i)
 * 
 * @param matrix [in]
 * @param os [out]
 */
// template <typename Derived>
// void pack_row(Eigen::PlainObjectBase<Derived>& matrix, octetStreams& os) {
//     assert(matrix.rows() == os.size());
//     const auto* ptr = matrix.data();
//     size_t size_row = matrix.cols() * sizeof(gfpScalar);
//     for (size_t i = 0; i < matrix.rows(); i++) {
//         os[i].append((octet*)ptr, size_row);
//         ptr += matrix.cols();
//     }
// }

/**
 * @brief Unpack the matrix.row(i) from the octetSream os(i)
 * 
 * @param matrix [out]
 * @param os [in]
 */
// template <typename Derived>
// void unpack_row(Eigen::PlainObjectBase<Derived>& matrix, octetStreams& os) {
//     assert(matrix.rows() == os.size());
//     const auto* ptr = matrix.data();
//     size_t size_row = matrix.cols() * sizeof(gfpScalar);
//     for (size_t i = 0; i < matrix.rows(); i++) {
//         // In the reconstruction, os[P] is empty to avoid loopback.
//         if (os[i].get_length()) {
//             os[i].consume((octet*)ptr, size_row);
//         }
//         ptr += matrix.cols();
//     }
// }

/**
 * @brief Pack the block of matrix into the octetStream.
 * 
 * @tparam Derived 
 * @param matrix [in]
 * @param startRow start row of the block
 * @param nRows number of rows in the block.
 * @param o [out]octetStream
 */
// template <typename Derived>
// void pack_rows(Eigen::PlainObjectBase<Derived>& matrix, const size_t& startRow, const size_t& nRows, octetStream& o) {
//     const auto* ptr = matrix.data();
//     ptr += startRow * matrix.cols();
//     o.append((octet*)ptr, nRows * matrix.cols() * sizeof(gfpScalar));
// }

/**
 * @brief Unpack the octetStream to the corresponding block of the matrix.
 * 
 * @tparam Derived 
 * @param matrix [out]
 * @param startRow start row of the block
 * @param nRows number of rows in the block.
 * @param o [in]
 */
// template <typename Derived>
// void unpack_rows(Eigen::PlainObjectBase<Derived>& matrix, const size_t& startRow, const size_t& nRows, octetStream& o) {
//     const auto* ptr = matrix.data();
//     ptr += startRow * matrix.cols();
//     o.consume((octet*)ptr, nRows * matrix.cols() * sizeof(gfpScalar));
// }

/**
 * @brief Pack several rows into os[i]. 
 * The partition is row-grained.
 * @tparam Derived 
 * @param matrix 
 * @param os 
 */
// template <typename Derived>
// void pack_rows(Eigen::PlainObjectBase<Derived>& matrix, octetStreams& os) {
//     assert(os.size());
//     size_t n_rows       = matrix.rows() / os.size();                 // Each block contains 'n_rows'
//     size_t first_n_rows = matrix.rows() - n_rows * (os.size() - 1);  // First block contains slightly more rows.
//     const auto* ptr     = matrix.data();

//     // Pack the corresponding block into the octetStream.
//     size_t first_n_gfp = first_n_rows * matrix.cols();
//     size_t n_gfp       = n_rows * matrix.cols();
//     os[0].append((octet*)ptr, first_n_gfp * sizeof(gfpScalar));
//     ptr += first_n_gfp;
//     for (size_t i = 1; i < os.size(); i++) {
//         os[i].append((octet*)ptr, n_gfp * sizeof(gfpScalar));
//         ptr += n_gfp;
//     }
// }

// Unpack the os[i] to the corresponding block of the matrix
// template <typename Derived>
// void unpack_rows(Eigen::PlainObjectBase<Derived>& matrix, octetStreams& os) {
//     assert(os.size());
//     size_t n_rows       = matrix.rows() / os.size();
//     size_t first_n_rows = matrix.rows() - n_rows * (os.size() - 1);
//     const auto* ptr     = matrix.data();

//     size_t first_n_gfp = first_n_rows * matrix.cols();
//     size_t n_gfp       = n_rows * matrix.cols();

//     if (os[0].get_length()) {
//         os[0].consume((octet*)ptr, first_n_gfp * sizeof(gfpScalar));
//     }
//     ptr += first_n_gfp;

//     for (size_t i = 1; i < os.size(); i++) {
//         if (os[i].get_length()) {
//             os[i].consume((octet*)ptr, n_gfp * sizeof(gfpScalar));
//         }
//         ptr += n_gfp;
//     }
// }

/**
 * @brief Pack the whole matrix into the octetStream o
 * 
 * @param matrix [in]
 * @param o [out]
 */
// template <typename Derived>
// void pack_matrix(Eigen::PlainObjectBase<Derived>& matrix, octetStream& o) {
//     o.append((octet*)matrix.data(), matrix.size() * sizeof(gfpScalar));
// }

/**
 * @brief Unpck the whole matrix from the octetStream o
 * 
 * @param matrix [out]
 * @param o [in]
 */
// template <typename Derived>
// void unpack_matrix(Eigen::PlainObjectBase<Derived>& matrix, octetStream& o) {
//     o.consume((octet*)matrix.data(), matrix.size() * sizeof(gfpScalar));
// }

inline void getMSB_matrix(const gfpMatrix& input, gfpMatrix& res) {
    for (size_t i = 0; i < input.size(); i++) {
        res(i) = input(i).msb();
    }
}

template <typename Derived>
void decompose_bits(gfpScalar x, const size_t& bit_length, Eigen::MatrixBase<Derived>& res) {
    assert(res.cols() == bit_length);
    assert(res.rows() == 1);
    res.setConstant(0);
    int idx = 0;
    while (!x.is_zero()) {
        res(idx) = x & 1;
        idx++;
        x >>= 1;
    }
}

template <typename Derived>
void decompose_bits(gfpVector x, const size_t& bit_length, Eigen::MatrixBase<Derived>& res) {
    assert(res.cols() == bit_length);
    assert(res.rows() == x.size());
    res.setConstant(0);
    for (size_t i = 0; i < x.size(); i++) {
        int idx = 0;
        while (!x(i).is_zero()) {
            res(i, idx) = x(i) & 1;
            idx++;
            x(i) >>= 1;
        }
    }
}

// Evaluate the prefix-products. (for batch inversion)
template <typename Derived>
void prefixMult(const Eigen::MatrixBase<Derived>& a, Eigen::MatrixBase<Derived>& res) {
    assert(a.size() == res.size());
    res(0) = a(0);
    for (size_t i = 1; i < a.size(); i++) {
        res(i) = res(i - 1) * a(i);
    }
}

// Batch Inversion: Compute n inverse by 3(n-1) multiplications and a single inversion
inline void batch_inversion(const gfpMatrix& a, gfpMatrix& a_inv) {
    assert(a.rows() == a_inv.rows());
    assert(a.cols() == a_inv.cols());
    gfpMatrix a_prefix_mult(a.rows(), a.cols());
    // p_i = p_i-1 * a_i
    prefixMult(a, a_prefix_mult);

    gfpMatrix a_prefix_inv(a.rows(), a.cols());
    gfpScalar inv_all = a_prefix_mult(a.rows() - 1, a.cols() - 1);
    inv_all.inverse();
    // q_n = 1/p_n
    // q_i-1 = q_i * a_i
    a_prefix_inv(a.size() - 1) = inv_all;
    for (size_t i = a.size() - 1; i >= 1; i--) {
        a_prefix_inv(i - 1) = a_prefix_inv(i) * a(i);
    }

    // a_inv_0 = q_0
    // a_inv_i = p_i-1 * q_i
    a_inv(0) = a_prefix_inv(0);
    a_inv.reshaped<Eigen::RowMajor>()(Eigen::seqN(1, a.size() - 1)) =
        a_prefix_mult.reshaped<Eigen::RowMajor>()(Eigen::seqN(0, a.size() - 1)).array() *
        a_prefix_inv.reshaped<Eigen::RowMajor>()(Eigen::seqN(1, a.size() - 1)).array();
}

template <typename Derived>
const Eigen::Reshaped<const Derived> reshape_helper(const Eigen::MatrixBase<Derived>& m, int rows, int cols) {
    return Eigen::Reshaped<const Derived>(m.derived(), rows, cols);
}

//a is zero padded into b (initialized to zeros) with parameters as passed:
//imageWidth, imageHeight, padding, inputFilters, batchSize
template <typename Derived>
void zeroPad(const Eigen::MatrixBase<Derived>& a, Eigen::MatrixBase<Derived>& b, size_t iw, size_t ih, size_t P,
             size_t Din, size_t B) {
    size_t size_B   = (iw + 2 * P) * (ih + 2 * P) * Din;
    size_t size_Din = (iw + 2 * P) * (ih + 2 * P);
    size_t size_w   = (iw + 2 * P);
    // rows() = the batchSize
    assert(a.rows() == B);
    assert(b.rows() == B);
    for (size_t i = 0; i < B; i++)
        for (size_t j = 0; j < Din; j++)
            for (size_t k = 0; k < ih; k++)
                for (size_t l = 0; l < iw; l++) {
                    b(i, j * size_Din + (k + P) * size_w + l + P) = a(i, j * iw * ih + k * iw + l);
                }
}

// Extend a to b for convolution.
//imageWidth, imageHeight, outputWeight, outpuHeight, inputFilters, stepStride, filterSize, batchSize
// For image 2*2 with two features, the storage is feature1(2*2) feature2(2*2)
inline void convolExtend(const gfpMatrix& a, gfpMatrix& b, size_t iw, size_t ih, size_t ow, size_t oh, size_t Din,
                         size_t S, size_t f, size_t B) {
    assert(b.rows() == B * ow * oh);
    assert(b.cols() == f * f * Din);
    for (size_t i = 0; i < B; i++) {
        // auto img = reshape_helper(a.row(i), ih, iw*Din);
        const gfpMatrix& img = a.row(i).reshaped<RowMajor>(ih * Din, iw);
        for (size_t j = 0; j < oh; j++)
            for (size_t k = 0; k < ow; k++) {
                // for each feature
                for (size_t w = 0; w < Din; w++) {
                    b.row(i * ow * oh + j * ow + k).segment(w * f * f, f * f) =
                        img.block(w * ih + j * S, k * S, f, f).reshaped<RowMajor>(1, f * f);
                }
            }
    }
}

inline void maxpoolExtend(const gfpMatrix& a, gfpMatrix& b, size_t iw, size_t ih, size_t ow, size_t oh, size_t Din,
                          size_t S, size_t f, size_t B) {
    assert(b.rows() == B * ow * oh * Din);
    assert(b.cols() == f * f);
    for (size_t i = 0; i < B; i++) {
        // auto img = reshape_helper(a.row(i), ih, iw*Din);
        const gfpMatrix& img = a.row(i).reshaped<RowMajor>(ih * Din, iw);
        for (size_t w = 0; w < Din; w++)  // for each feature
            for (size_t j = 0; j < oh; j++)
                for (size_t k = 0; k < ow; k++) {
                    // b.row(i*ow*oh + j*ow + k).segment(w*f*f, f*f) = img.block(w*ih+j*S, k*S, f, f).reshaped<RowMajor>(1, f*f);
                    b.row(i * ow * oh * Din + w * ow * oh + j * ow + k) =
                        img.block(w * ih + j * S, k * S, f, f).reshaped<RowMajor>(1, f * f);
                }
    }
}

inline void print_oneline(const RowMatrixXd& matrix, std::string str) {
#ifdef DEBUG_NN
    cout << str << matrix.reshaped<Eigen::RowMajor>(1, matrix.size()) << endl;
#endif
}

class FieldArray {
public:
    int party      = PUBLIC;
    int size       = 0;        // size of array
    uint64_t* data = nullptr;  // data (ell-bit integers)
    bool signed_;              // signed? (1: signed; 0: unsigned)
    int ell;                   // field
    int s;                     // scale

    FieldArray(){};

    FieldArray(int party_, int sz, bool signed__, int ell_, int s_ = 0) {
        assert(party_ == PUBLIC || party_ == ALICE || party_ == BOB);
        assert(sz > 0);
        assert(ell_ < std::numeric_limits<uint64_t>::max() && ell_ > 0);
        this->party   = party_;
        this->size    = sz;
        this->signed_ = signed__;
        this->ell     = ell_;
        this->s       = s_;
        data          = new uint64_t[sz];
    }
    // copy constructor
    FieldArray(const FieldArray& other) {
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = new uint64_t[size];
        memcpy(this->data, other.data, size * sizeof(uint64_t));
    }

    // move constructor
    FieldArray(FieldArray&& other) noexcept {
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = other.data;
        other.data    = nullptr;
    }
    ~FieldArray() {
        delete[] data;
    }

    template <class T>
    std::vector<T> get_native_type() const;

    // copy assignment
    FieldArray& operator=(const FieldArray& other) {
        if (this == &other)
            return *this;

        delete[] this->data;
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = new uint64_t[size];
        memcpy(this->data, other.data, size * sizeof(uint64_t));
        return *this;
    }

    // move assignment
    FieldArray& operator=(FieldArray&& other) noexcept {
        if (this == &other)
            return *this;

        delete[] this->data;
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = other.data;
        other.data    = nullptr;
        return *this;
    }

    // FieldArray[i, j)
    FieldArray subset(int i, int j);

    uint64_t ell_mask() const {
        return ((ell == std::numeric_limits<uint64_t>::max()) ? -1 : std::numeric_limits<uint64_t>::max() - 1);
    }
};

}  // namespace nisl

#endif