#ifndef BOOL_OP_H__
#define BOOL_OP_H__

#include "bool-data.h"
#include "io_pack.h"
#include "ot_pack.h"
#include "aux-protocols.h"

#define I 0
#define J 1
#define print_bool(vec)                                               \
    {                                                                 \
        auto tmp_pub = bool_op->output(PUBLIC, vec).subset(I, I + J); \
        cout << #vec << "_pub: " << tmp_pub << endl;                  \
    }

namespace nisl
{

    class BoolOp
    {
        friend class FixOp;
        friend class FPMath;

    private:
        IOPack *iopack;
        OTPack *otpack;
        AuxProtocols *aux;

    public:
        int party;

        BoolOp(int party, IOPack *iopack, OTPack *otpack)
        {
            this->party = party;
            this->iopack = iopack;
            this->otpack = otpack;
            this->aux = new AuxProtocols(party, iopack, otpack);
        }

        ~BoolOp() { delete aux; }

        // input functions: return a BoolArray that stores data_
        // party_ denotes which party provides the input data_ and the data_ provided by the other party is ignored. If party_ is PUBLIC, then the data_ provided by both parties must be identical.
        // sz is the size of the returned BoolArray and the uint8_t array pointed by data_
        BoolArray input(int party_, int sz, uint8_t *data_);
        // same as the above function, except that it replicates data_ in all sz positions of the returned BoolArray
        BoolArray input(int party_, int sz, uint8_t data_);

        // output function: returns the secret array underlying x in the form of a PUBLIC BoolArray
        // party_ denotes which party will receive the output. If party_ is PUBLIC, both parties receive the output.
        BoolArray output(int party_, const BoolArray &x);

        // Multiplexers: return x[i] if cond[i] = 1; else return y[i]
        // cond must be a secret-shared BoolArray
        //// Both x and y can be PUBLIC or secret-shared
        //// cond, x, y must have equal size
        BoolArray if_else(const BoolArray &cond, const BoolArray &x, const BoolArray &y);
        //// x can be PUBLIC or secret-shared
        //// cond, x must have equal size
        //// y[i] = y
        BoolArray if_else(const BoolArray &cond, const BoolArray &x, uint8_t y);
        //// y can be PUBLIC or secret-shared
        //// cond, y must have equal size
        //// x[i] = x
        BoolArray if_else(const BoolArray &cond, uint8_t x, const BoolArray &y);

        // NOT Gate: return ! x[i]
        BoolArray NOT(const BoolArray &x);

        // Boolean Arithmetic Gates: return x[i] OP y[i], OP = {^, &, |}
        // x and y must have equal size
        //// Both x and y can be PUBLIC or secret-shared
        BoolArray XOR(const BoolArray &x, const BoolArray &y);
        //// At least one of x and y must be a secret-shared BoolArray
        BoolArray AND(const BoolArray &x, const BoolArray &y);
        //// At least one of x and y must be a secret-shared BoolArray
        BoolArray OR(const BoolArray &x, const BoolArray &y);
    };

    // prints the contents of other, which must be a PUBLIC BoolArray
    std::ostream &operator<<(std::ostream &os, BoolArray &other);
} // end namespace nisl

#endif