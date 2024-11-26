#ifndef RING_DATA_H__
#define RING_DATA_H__

#include "emp-tool.h"  // add consts:PUBLIC ALICE BOB

namespace nisl {
class FixArray {
public:
    int party      = PUBLIC;
    int size       = 0;        // size of array
    uint64_t* data = nullptr;  // data (ell-bit integers)
    bool signed_;              // signed? (1: signed; 0: unsigned)
    int ell;                   // field
    int s;                     // scale

    FixArray() {};

    FixArray(int party_, int sz, bool signed__, int ell_, int s_ = 0) {
        assert(party_ == PUBLIC || party_ == ALICE || party_ == BOB);
        assert(sz > 0);
        assert(ell_ <= 64 && ell_ > 0);
        this->party   = party_;
        this->size    = sz;
        this->signed_ = signed__;
        this->ell     = ell_;
        this->s       = s_;
        data          = new uint64_t[sz];
    }

    // copy constructor
    FixArray(const FixArray& other) {
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = new uint64_t[size];
        memcpy(this->data, other.data, size * sizeof(uint64_t));
    }

    // move constructor
    FixArray(FixArray&& other) noexcept {
        this->party   = other.party;
        this->size    = other.size;
        this->signed_ = other.signed_;
        this->ell     = other.ell;
        this->s       = other.s;
        this->data    = other.data;
        other.data    = nullptr;
    }

    ~FixArray() {
        delete[] data;
    }

    template <class T>
    std::vector<T> get_native_type() const;

    // copy assignment
    FixArray& operator=(const FixArray& other) {
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
    FixArray& operator=(FixArray&& other) noexcept {
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

    // FixArray[i, j)
    FixArray subset(int i, int j);

    uint64_t ell_mask() const {
        return ((ell == 64) ? -1 : (1ULL << (this->ell)) - 1);
    }
};

}  // namespace nisl

#endif