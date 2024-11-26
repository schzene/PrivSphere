
#ifndef BOOL_DATA_H__
#define BOOL_DATA_H__

#include "emp-tool.h" // add consts:PUBLIC ALICE BOB

namespace nisl
{ // A container to hold an array of boolean values
    // If party is set as PUBLIC for a BoolArray instance, then the underlying array is known publicly and we maintain the invariant that both parties will hold identical data in that instance.
    // Else, the underlying array is secret-shared and the class instance will hold the party's share of the secret array. In this case, the party data member denotes which party this share belongs to.
    class BoolArray
    {
    public:
        int party = PUBLIC;
        int size = 0;            // size of array
        uint8_t *data = nullptr; // data

        BoolArray() {};

        BoolArray(int party_, int sz)
        {
            assert(party_ == PUBLIC || party_ == ALICE || party_ == BOB);
            assert(sz > 0);
            this->party = party_;
            this->size = sz;
            data = new uint8_t[sz];
        }

        // copy constructor
        BoolArray(const BoolArray &other)
        {
            this->size = other.size;
            this->party = other.party;
            this->data = new uint8_t[size];
            memcpy(this->data, other.data, size * sizeof(uint8_t));
        }

        // move constructor
        BoolArray(BoolArray &&other) noexcept
        {
            this->size = other.size;
            this->party = other.party;
            this->data = other.data;
            other.data = nullptr;
        }

        ~BoolArray() { delete[] data; }

        // copy assignment
        BoolArray &operator=(const BoolArray &other)
        {
            if (this == &other)
                return *this;

            delete[] this->data;
            this->size = other.size;
            this->party = other.party;
            this->data = new uint8_t[size];
            memcpy(this->data, other.data, size * sizeof(uint8_t));
            return *this;
        }

        // move assignment
        BoolArray &operator=(BoolArray &&other) noexcept
        {
            if (this == &other)
                return *this;

            delete[] this->data;
            this->size = other.size;
            this->party = other.party;
            this->data = other.data;
            other.data = nullptr;
            return *this;
        }

        // BoolArray[i, j)
        BoolArray subset(int i, int j);
    };

} // end namespace nisl
#endif // BOOL_DATA_H__