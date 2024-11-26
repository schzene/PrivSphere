#ifndef FIELD_DATA_H_
#define FIELD_DATA_H_

#include "emp-tool.h"  // add const:PUBLIC ALICE BOB

namespace nisl {

class FieldArray {
public:
    int party      = PUBLIC;
    int size       = 0;        // size of array
    uint64_t* data = nullptr;  // data (ell-bit integers)
    bool signed_;              // signed? (1: signed; 0: unsigned)
    int ell;                   // field
    int s;                     // scale

    FieldArray() {};

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