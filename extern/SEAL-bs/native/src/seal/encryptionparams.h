// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#pragma once

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
#include <seal/seal.h>

=======
#include "seal/memorymanager.h"
#include "seal/modulus.h"
#include "seal/randomgen.h"
#include "seal/serialization.h"
#include "seal/version.h"
#include "seal/util/defines.h"
#include "seal/util/globals.h"
#include "seal/util/hash.h"
#include "seal/util/ztools.h"
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
namespace nexus {
namespace seal_bs {
/**
    The data type to store unique identifiers of encryption parameters.
    */
using parms_id_type = seal::util::HashFunction::hash_block_type;
=======
namespace seal
{
    /**
    Describes the type of encryption scheme to be used.
    */
    enum class scheme_type : std::uint8_t
    {
        // No scheme set; cannot be used for encryption
        none = 0x0,

        // Brakerski/Fan-Vercauteren scheme
        bfv = 0x1,

        // Cheon-Kim-Kim-Song scheme
        ckks = 0x2,

        // Brakerski-Gentry-Vaikuntanathan scheme
        bgv = 0x3
    };

    /**
    The data type to store unique identifiers of encryption parameters.
    */
    using parms_id_type = util::HashFunction::hash_block_type;
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

/**
    A parms_id_type value consisting of zeros.
    */
extern const parms_id_type parms_id_zero;

/**
    Represents user-customizable encryption scheme settings. The parameters (most
    importantly poly_modulus, coeff_modulus, plain_modulus) significantly affect
    the performance, capabilities, and security of the encryption scheme. Once
    an instance of EncryptionParameters is populated with appropriate parameters,
    it can be used to create an instance of the SEALContext class, which verifies
    the validity of the parameters, and performs necessary pre-computations.

    Picking appropriate encryption parameters is essential to enable a particular
    application while balancing performance and security. Some encryption settings
    will not allow some inputs (e.g. attempting to encrypt a polynomial with more
    coefficients than poly_modulus or larger coefficients than plain_modulus) or,
    support the desired computations (with noise growing too fast due to too large
    plain_modulus and too small coeff_modulus).

    @par parms_id
    The EncryptionParameters class maintains at all times a 256-bit hash of the
    currently set encryption parameters called the parms_id. This hash acts as
    a unique identifier of the encryption parameters and is used by all further
    objects created for these encryption parameters. The parms_id is not intended
    to be directly modified by the user but is used internally for pre-computation
    data lookup and input validity checks. In modulus switching the user can use
    the parms_id to keep track of the chain of encryption parameters. The parms_id
    is not exposed in the public API of EncryptionParameters, but can be accessed
    through the SEALContext::ContextData class once the SEALContext has been created.

    @par Thread Safety
    In general, reading from EncryptionParameters is thread-safe, while mutating
    is not.

    @warning Choosing inappropriate encryption parameters may lead to an encryption
    scheme that is not secure, does not perform well, and/or does not support the
    input and computation of the desired application. We highly recommend consulting
    an expert in RLWE-based encryption when selecting parameters, as this is where
    inexperienced users seem to most often make critical mistakes.
    */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
class EncryptionParameters : public seal::EncryptionParameters {
    friend struct std::hash<EncryptionParameters>;
=======
    class EncryptionParameters
    {
        friend struct std::hash<EncryptionParameters>;
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

public:
    /**
        Creates an empty set of encryption parameters.

        @param[in] scheme The encryption scheme to be used
        @see scheme_type for the supported schemes
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    EncryptionParameters(seal::scheme_type scheme = seal::scheme_type::none) : scheme_(scheme) {
        compute_parms_id();
    }
=======
        EncryptionParameters(scheme_type scheme = scheme_type::none) : scheme_(scheme)
        {
            compute_parms_id();
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Creates an empty set of encryption parameters.

        @param[in] scheme The encryption scheme to be used
        @throws std::invalid_argument if scheme is not supported
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    EncryptionParameters(std::uint8_t scheme) {
        // Check that a valid scheme is given
        if (!is_valid_scheme(scheme)) {
            throw std::invalid_argument("unsupported scheme");
=======
        EncryptionParameters(std::uint8_t scheme)
        {
            // Check that a valid scheme is given
            if (!is_valid_scheme(scheme))
            {
                throw std::invalid_argument("unsupported scheme");
            }

            scheme_ = static_cast<scheme_type>(scheme);
            compute_parms_id();
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h
        }

        scheme_ = static_cast<seal::scheme_type>(scheme);
        compute_parms_id();
    }

    /**
        Creates a copy of a given instance of EncryptionParameters.

        @param[in] copy The EncryptionParameters to copy from
        */
    EncryptionParameters(const EncryptionParameters& copy) = default;

    /**
        Overwrites the EncryptionParameters instance with a copy of a given instance.

        @param[in] assign The EncryptionParameters to copy from
        */
    EncryptionParameters& operator=(const EncryptionParameters& assign) = default;

    /**
        Creates a new EncryptionParameters instance by moving a given instance.

        @param[in] source The EncryptionParameters to move from
        */
    EncryptionParameters(EncryptionParameters&& source) = default;

    /**
        Overwrites the EncryptionParameters instance by moving a given instance.

        @param[in] assign The EncryptionParameters to move from
        */
    EncryptionParameters& operator=(EncryptionParameters&& assign) = default;

    /**
        Sets the degree of the polynomial modulus parameter to the specified value.
        The polynomial modulus directly affects the number of coefficients in
        plaintext polynomials, the size of ciphertext elements, the computational
        performance of the scheme (bigger is worse), and the security level (bigger
        is better). In Microsoft SEAL the degree of the polynomial modulus must be
        a power of 2 (e.g.  1024, 2048, 4096, 8192, 16384, or 32768).

        @param[in] poly_modulus_degree The new polynomial modulus degree
        @throws std::logic_error if a valid scheme is not set and poly_modulus_degree
        is non-zero
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_poly_modulus_degree(std::size_t poly_modulus_degree) {
        if (scheme_ == seal::scheme_type::none && poly_modulus_degree) {
            throw std::logic_error("poly_modulus_degree is not supported for this scheme (from SEAL-bs)");
        }
=======
        inline void set_poly_modulus_degree(std::size_t poly_modulus_degree)
        {
            if (scheme_ == scheme_type::none && poly_modulus_degree)
            {
                throw std::logic_error("poly_modulus_degree is not supported for this scheme");
            }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

        // Set the degree
        poly_modulus_degree_ = poly_modulus_degree;

        // Re-compute the parms_id
        compute_parms_id();
    }

    /*
        J.-W. Lee: newly inserted for secret key hamming weight. The original 
        SEAL library uses only the uniform ternary secret key distribution.
        Since the bootstrapping requires sparse secret key distrubition for 
        some parameters, the secret key hamming weight is added in 
        EncryptionParameters as a member variable. If the secret key distribution
        is not sparse, the secret key hamming weight is set to be zero. Non-zero
        secret key hamming weight means the sparse secret key distribution.

        @param[in] secret_key_hamming_weight The new secret key hamming weight 
        @throws std::logic_error if a valid scheme is not set and secret key
        hamming weight is non-zero
        */

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_secret_key_hamming_weight(std::size_t secret_key_hamming_weight) {
        if (scheme_ == seal::scheme_type::none && secret_key_hamming_weight) {
            throw std::logic_error("secret key hamming weight is not supported for this scheme");
        }
=======
        inline void set_secret_key_hamming_weight(std::size_t secret_key_hamming_weight)
        {
            if (scheme_ == scheme_type::none && secret_key_hamming_weight)
            {
                throw std::logic_error("secret key hamming weight is not supported for this scheme");
            }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

        // Set the degree
        secret_key_hamming_weight_ = secret_key_hamming_weight;

        // Re-compute the parms_id
        compute_parms_id();
    }

    /*
        J.-W. Lee: newly inserted for the number of sparse slots. The original 
        SEAL library uses only the full slot, which is the half of polynomial 
        modulus degree. However, the runtime of the bootstrapping is affected
        by the number of sparse slots, and thus we add the number of sparse
        slots as a member variable. The number of sparse slots should be 
        positive power-of-two integer less than polynomial modulus degree.
        If the full slot is used, the sparse_slots is set to be zero. Non-zero
        sparse_slots means to use the sparse slot.

        @param[in] sparse_slots The number of sparse slots 
        @throws std::logic_error if a valid scheme is not set and sparse_slots
        is non-zero, or if sparse_slots is not power-of-two integer or zero.
        */

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_sparse_slots(std::size_t sparse_slots) {
        if (scheme_ == seal::scheme_type::none && sparse_slots) {
            throw std::logic_error("secret key hamming weight is not supported for this scheme");
        }
=======
        inline void set_sparse_slots(std::size_t sparse_slots)
        {
            if (scheme_ == scheme_type::none && sparse_slots)
            {
                throw std::logic_error("secret key hamming weight is not supported for this scheme");
            }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

        if ((sparse_slots & (sparse_slots - 1)) != 0) {
            throw std::logic_error("secret key hamming weight is not zero or power-of-two");
        }

        // Set the degree
        sparse_slots_ = sparse_slots;

        // Re-compute the parms_id
        compute_parms_id();
    }

    /**
        Sets the coefficient modulus parameter. The coefficient modulus consists
        of a list of distinct prime numbers, and is represented by a vector of
        Modulus objects. The coefficient modulus directly affects the size
        of ciphertext elements, the amount of computation that the scheme can
        perform (bigger is better), and the security level (bigger is worse). In
        Microsoft SEAL each of the prime numbers in the coefficient modulus must
        be at most 60 bits, and must be congruent to 1 modulo 2*poly_modulus_degree.

        @param[in] coeff_modulus The new coefficient modulus
        @throws std::logic_error if a valid scheme is not set and coeff_modulus is
        is non-empty
        @throws std::invalid_argument if size of coeff_modulus is invalid
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_coeff_modulus(const std::vector<seal::Modulus>& coeff_modulus) {
        // Check that a scheme is set
        if (scheme_ == seal::scheme_type::none) {
            if (!coeff_modulus.empty()) {
                throw std::logic_error("coeff_modulus is not supported for this scheme");
=======
        inline void set_coeff_modulus(const std::vector<Modulus> &coeff_modulus)
        {
            // Check that a scheme is set
            if (scheme_ == scheme_type::none)
            {
                if (!coeff_modulus.empty())
                {
                    throw std::logic_error("coeff_modulus is not supported for this scheme");
                }
            }
            else if (coeff_modulus.size() > SEAL_COEFF_MOD_COUNT_MAX || coeff_modulus.size() < SEAL_COEFF_MOD_COUNT_MIN)
            {
                throw std::invalid_argument("coeff_modulus is invalid");
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h
            }
        }
        else if (coeff_modulus.size() > SEAL_COEFF_MOD_COUNT_MAX || coeff_modulus.size() < SEAL_COEFF_MOD_COUNT_MIN) {
            throw std::invalid_argument("coeff_modulus is invalid");
        }

        coeff_modulus_ = coeff_modulus;

        // Re-compute the parms_id
        compute_parms_id();
    }

    /**
        Sets the plaintext modulus parameter. The plaintext modulus is an integer
        modulus represented by the Modulus class. The plaintext modulus
        determines the largest coefficient that plaintext polynomials can represent.
        It also affects the amount of computation that the scheme can perform
        (bigger is worse). In Microsoft SEAL the plaintext modulus can be at most
        60 bits long, but can otherwise be any integer. Note, however, that some
        features (e.g. batching) require the plaintext modulus to be of a particular
        form.

        @param[in] plain_modulus The new plaintext modulus
        @throws std::logic_error if scheme is not scheme_type::BFV and plain_modulus
        is non-zero
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_plain_modulus(const seal::Modulus& plain_modulus) {
        // Check that scheme is BFV
        if (scheme_ != seal::scheme_type::bfv && scheme_ != seal::scheme_type::bgv && !plain_modulus.is_zero()) {
            throw std::logic_error("plain_modulus is not supported for this scheme");
        }
=======
        inline void set_plain_modulus(const Modulus &plain_modulus)
        {
            // Check that scheme is BFV
            if (scheme_ != scheme_type::bfv && scheme_ != scheme_type::bgv && !plain_modulus.is_zero())
            {
                throw std::logic_error("plain_modulus is not supported for this scheme");
            }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

        plain_modulus_ = plain_modulus;

        // Re-compute the parms_id
        compute_parms_id();
    }

    /**
        Sets the plaintext modulus parameter. The plaintext modulus is an integer
        modulus represented by the Modulus class. This constructor instead
        takes a std::uint64_t and automatically creates the Modulus object.
        The plaintext modulus determines the largest coefficient that plaintext
        polynomials can represent. It also affects the amount of computation that
        the scheme can perform (bigger is worse). In Microsoft SEAL the plaintext
        modulus can be at most 60 bits long, but can otherwise be any integer. Note,
        however, that some features (e.g. batching) require the plaintext modulus
        to be of a particular form.

        @param[in] plain_modulus The new plaintext modulus
        @throws std::invalid_argument if plain_modulus is invalid
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_plain_modulus(std::uint64_t plain_modulus) {
        set_plain_modulus(seal::Modulus(plain_modulus));
    }
=======
        inline void set_plain_modulus(std::uint64_t plain_modulus)
        {
            set_plain_modulus(Modulus(plain_modulus));
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Sets the random number generator factory to use for encryption. By default,
        the random generator is set to UniformRandomGeneratorFactory::default_factory().
        Setting this value allows a user to specify a custom random number generator
        source.

        @param[in] random_generator Pointer to the random generator factory
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline void set_random_generator(std::shared_ptr<seal::UniformRandomGeneratorFactory> random_generator) noexcept {
        random_generator_ = std::move(random_generator);
    }
=======
        inline void set_random_generator(std::shared_ptr<UniformRandomGeneratorFactory> random_generator) noexcept
        {
            random_generator_ = std::move(random_generator);
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Returns the encryption scheme type.
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD inline seal::scheme_type scheme() const noexcept {
        return scheme_;
    }
=======
        SEAL_NODISCARD inline scheme_type scheme() const noexcept
        {
            return scheme_;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Returns the degree of the polynomial modulus parameter.
        */
    SEAL_NODISCARD inline std::size_t poly_modulus_degree() const noexcept {
        return poly_modulus_degree_;
    }

    /**
        J.-W. Lee: Returns the secret key hamming weight.
        */
    SEAL_NODISCARD inline std::size_t secret_key_hamming_weight() const noexcept {
        return secret_key_hamming_weight_;
    }

    /**
        J.-W. Lee: Returns the number of sparse slots. (zero means the full slots)
        */
    SEAL_NODISCARD inline std::size_t sparse_slots() const noexcept {
        return sparse_slots_;
    }

    /**
        Returns a const reference to the currently set coefficient modulus parameter.
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD inline const std::vector<seal::Modulus>& coeff_modulus() const noexcept {
        return coeff_modulus_;
    }
=======
        SEAL_NODISCARD inline const std::vector<Modulus> &coeff_modulus() const noexcept
        {
            return coeff_modulus_;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Returns a const reference to the currently set plaintext modulus parameter.
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD inline const seal::Modulus& plain_modulus() const noexcept {
        return plain_modulus_;
    }
=======
        SEAL_NODISCARD inline const Modulus &plain_modulus() const noexcept
        {
            return plain_modulus_;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Returns a pointer to the random number generator factory to use for encryption.
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD inline std::shared_ptr<seal::UniformRandomGeneratorFactory> random_generator() const noexcept {
        return random_generator_;
    }
=======
        SEAL_NODISCARD inline std::shared_ptr<UniformRandomGeneratorFactory> random_generator() const noexcept
        {
            return random_generator_;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Returns a const reference to the parms_id of the current parameters.
        */
    SEAL_NODISCARD inline const parms_id_type& parms_id() const noexcept {
        return parms_id_;
    }

    /**
        Compares a given set of encryption parameters to the current set of
        encryption parameters. The comparison is performed by comparing the
        parms_ids of the parameter sets rather than comparing the parameters
        individually.

        @parms[in] other The EncryptionParameters to compare against
        */
    SEAL_NODISCARD inline bool operator==(const EncryptionParameters& other) const noexcept {
        return (parms_id_ == other.parms_id_);
    }

    /**
        Compares a given set of encryption parameters to the current set of
        encryption parameters. The comparison is performed by comparing
        parms_ids of the parameter sets rather than comparing the parameters
        individually.

        @parms[in] other The EncryptionParameters to compare against
        */
    SEAL_NODISCARD inline bool operator!=(const EncryptionParameters& other) const noexcept {
        return (parms_id_ != other.parms_id_);
    }

    /**
        Returns an upper bound on the size of the EncryptionParameters, as if it
        was written to an output stream.

        @param[in] compr_mode The compression mode
        @throws std::invalid_argument if the compression mode is not supported
        @throws std::logic_error if the size does not fit in the return type
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD inline std::streamoff save_size(
        seal::compr_mode_type compr_mode = seal::Serialization::compr_mode_default) const {
        std::size_t coeff_modulus_total_size =
            coeff_modulus_.empty() ?
                std::size_t(0) :
                seal::util::safe_cast<std::size_t>(coeff_modulus_[0].save_size(seal::compr_mode_type::none));
        coeff_modulus_total_size = seal::util::mul_safe(coeff_modulus_total_size, coeff_modulus_.size());

        std::size_t members_size = seal::Serialization::ComprSizeEstimate(
            seal::util::add_safe(
                sizeof(scheme_),
                sizeof(std::uint64_t),  // poly_modulus_degree_
                sizeof(std::uint64_t),  // coeff_modulus_size
                coeff_modulus_total_size,
                seal::util::safe_cast<std::size_t>(plain_modulus_.save_size(seal::compr_mode_type::none))),
            compr_mode);

        return seal::util::safe_cast<std::streamoff>(
            seal::util::add_safe(sizeof(seal::Serialization::SEALHeader), members_size));
    }
=======
        SEAL_NODISCARD inline std::streamoff save_size(
            compr_mode_type compr_mode = Serialization::compr_mode_default) const
        {
            std::size_t coeff_modulus_total_size =
                coeff_modulus_.empty()
                    ? std::size_t(0)
                    : util::safe_cast<std::size_t>(coeff_modulus_[0].save_size(compr_mode_type::none));
            coeff_modulus_total_size = util::mul_safe(coeff_modulus_total_size, coeff_modulus_.size());

            std::size_t members_size = Serialization::ComprSizeEstimate(
                util::add_safe(
                    sizeof(scheme_),
                    sizeof(std::uint64_t), // poly_modulus_degree_
                    sizeof(std::uint64_t), // coeff_modulus_size
                    coeff_modulus_total_size,
                    util::safe_cast<std::size_t>(plain_modulus_.save_size(compr_mode_type::none))),
                compr_mode);

            return util::safe_cast<std::streamoff>(util::add_safe(sizeof(Serialization::SEALHeader), members_size));
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Saves EncryptionParameters to an output stream. The output is in binary
        format and is not human-readable. The output stream must have the "binary"
        flag set.

        @param[out] stream The stream to save the EncryptionParameters to
        @param[in] compr_mode The desired compression mode
        @throws std::invalid_argument if the compression mode is not supported
        @throws std::logic_error if the data to be saved is invalid, or if
        compression failed
        @throws std::runtime_error if I/O operations failed
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline std::streamoff save(std::ostream& stream,
                               seal::compr_mode_type compr_mode = seal::Serialization::compr_mode_default) const {
        using namespace std::placeholders;
        return seal::Serialization::Save(std::bind(&EncryptionParameters::save_members, this, _1),
                                         save_size(seal::compr_mode_type::none), stream, compr_mode, false);
    }
=======
        inline std::streamoff save(
            std::ostream &stream, compr_mode_type compr_mode = Serialization::compr_mode_default) const
        {
            using namespace std::placeholders;
            return Serialization::Save(
                std::bind(&EncryptionParameters::save_members, this, _1), save_size(compr_mode_type::none), stream,
                compr_mode, false);
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Loads EncryptionParameters from an input stream overwriting the current
        EncryptionParameters.

        @param[in] stream The stream to load the EncryptionParameters from
        @throws std::logic_error if the data cannot be loaded by this version of
        Microsoft SEAL, if the loaded data is invalid or if decompression failed
        @throws std::runtime_error if I/O operations failed
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline std::streamoff load(std::istream& stream) {
        using namespace std::placeholders;
        EncryptionParameters new_parms(seal::scheme_type::none);
        auto in_size = seal::Serialization::Load(std::bind(&EncryptionParameters::load_members, &new_parms, _1, _2),
                                                 stream, false);
        std::swap(*this, new_parms);
        return in_size;
    }
=======
        inline std::streamoff load(std::istream &stream)
        {
            using namespace std::placeholders;
            EncryptionParameters new_parms(scheme_type::none);
            auto in_size =
                Serialization::Load(std::bind(&EncryptionParameters::load_members, &new_parms, _1, _2), stream, false);
            std::swap(*this, new_parms);
            return in_size;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Saves EncryptionParameters to a given memory location. The output is in
        binary format and is not human-readable.

        @param[out] out The memory location to write the EncryptionParameters to
        @param[in] size The number of bytes available in the given memory location
        @param[in] compr_mode The desired compression mode
        @throws std::invalid_argument if out is null or if size is too small to
        contain a SEALHeader, or if the compression mode is not supported
        @throws std::logic_error if the data to be saved is invalid, or if
        compression failed
        @throws std::runtime_error if I/O operations failed
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline std::streamoff save(seal::seal_byte* out, std::size_t size,
                               seal::compr_mode_type compr_mode = seal::Serialization::compr_mode_default) const {
        using namespace std::placeholders;
        return seal::Serialization::Save(std::bind(&EncryptionParameters::save_members, this, _1),
                                         save_size(seal::compr_mode_type::none), out, size, compr_mode, false);
    }
=======
        inline std::streamoff save(
            seal_byte *out, std::size_t size, compr_mode_type compr_mode = Serialization::compr_mode_default) const
        {
            using namespace std::placeholders;
            return Serialization::Save(
                std::bind(&EncryptionParameters::save_members, this, _1), save_size(compr_mode_type::none), out, size,
                compr_mode, false);
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Loads EncryptionParameters from a given memory location overwriting the
        current EncryptionParameters.

        @param[in] in The memory location to load the EncryptionParameters from
        @param[in] size The number of bytes available in the given memory location
        @throws std::invalid_argument if in is null or if size is too small to
        contain a SEALHeader
        @throws std::logic_error if the data cannot be loaded by this version of
        Microsoft SEAL, if the loaded data is invalid, or if decompression failed
        @throws std::runtime_error if I/O operations failed
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    inline std::streamoff load(const seal::seal_byte* in, std::size_t size) {
        using namespace std::placeholders;
        EncryptionParameters new_parms(seal::scheme_type::none);
        auto in_size = seal::Serialization::Load(std::bind(&EncryptionParameters::load_members, &new_parms, _1, _2), in,
                                                 size, false);
        std::swap(*this, new_parms);
        return in_size;
    }
=======
        inline std::streamoff load(const seal_byte *in, std::size_t size)
        {
            using namespace std::placeholders;
            EncryptionParameters new_parms(scheme_type::none);
            auto in_size = Serialization::Load(
                std::bind(&EncryptionParameters::load_members, &new_parms, _1, _2), in, size, false);
            std::swap(*this, new_parms);
            return in_size;
        }
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    /**
        Enables access to private members of seal::EncryptionParameters for SEAL_C.
        */
    struct EncryptionParametersPrivateHelper;

private:
    /**
        Helper function to determine whether given std::uint8_t represents a valid
        value for scheme_type. The return value will be false is the scheme is set
        to scheme_type::none.
        */
<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    SEAL_NODISCARD bool is_valid_scheme(std::uint8_t scheme) const noexcept {
        switch (scheme) {
            case static_cast<std::uint8_t>(seal::scheme_type::none):
=======
        SEAL_NODISCARD bool is_valid_scheme(std::uint8_t scheme) const noexcept
        {
            switch (scheme)
            {
            case static_cast<std::uint8_t>(scheme_type::none):
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h
                /* fall through */

            case static_cast<std::uint8_t>(scheme_type::bfv):
                /* fall through */

            case static_cast<std::uint8_t>(scheme_type::ckks):
                /* fall through */

            case static_cast<std::uint8_t>(scheme_type::bgv):
                return true;
        }
        return false;
    }

    void compute_parms_id();

    void save_members(std::ostream& stream) const;

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    void load_members(std::istream& stream, seal::SEALVersion version);

    seal::MemoryPoolHandle pool_ = seal::MemoryManager::GetPool();

    seal::scheme_type scheme_;
=======
        void load_members(std::istream &stream, SEALVersion version);

        MemoryPoolHandle pool_ = MemoryManager::GetPool();

        scheme_type scheme_;
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h

    std::size_t poly_modulus_degree_ = 0;

    std::size_t secret_key_hamming_weight_ = 0;

    std::size_t sparse_slots_ = 0;

<<<<<<< HEAD:src/cryptools/he/nexustools/encryptionparams.h
    std::vector<seal::Modulus> coeff_modulus_{};

    std::shared_ptr<seal::UniformRandomGeneratorFactory> random_generator_{nullptr};

    seal::Modulus plain_modulus_{};

    parms_id_type parms_id_ = parms_id_zero;
};
}  // namespace seal_bs
}  // namespace nexus
=======
        std::vector<Modulus> coeff_modulus_{};

        std::shared_ptr<UniformRandomGeneratorFactory> random_generator_{ nullptr };

        Modulus plain_modulus_{};

        parms_id_type parms_id_ = parms_id_zero;
    };
} // namespace seal

/**
Specializes the std::hash template for parms_id_type.
*/
namespace std
{
    template <>
    struct hash<seal::parms_id_type>
    {
        std::size_t operator()(const seal::parms_id_type &parms_id) const
        {
            std::uint64_t result = 17;
            result = 31 * result + parms_id[0];
            result = 31 * result + parms_id[1];
            result = 31 * result + parms_id[2];
            result = 31 * result + parms_id[3];
            return static_cast<std::size_t>(result);
        }
    };

    template <>
    struct hash<seal::EncryptionParameters>
    {
        std::size_t operator()(const seal::EncryptionParameters &parms) const
        {
            hash<seal::parms_id_type> parms_id_hash;
            return parms_id_hash(parms.parms_id_);
        }
    };
} // namespace std
>>>>>>> parent of 47adabe... 删除不再使用的文件和配置，同时将SEAL-bs内置到NEXUS中:extern/SEAL-bs/native/src/seal/encryptionparams.h