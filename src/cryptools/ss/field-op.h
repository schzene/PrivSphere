#ifndef FIELD_OP_H__
#define FIELD_OP_H__

#include "aux-protocols.h"
#include "bool-op.h"
#include "comm_tool.h"
#include "emp-ot.h"
#include "equality.h"
#include "fieldtrunc.h"
#include "linear-ot.h"
#include "ring-data.h"
#include "value-extension.h"

/**
 * SS based op on field
 * including: intput output add sub if_else extend B2A mul left_shift right_shift trucate scale_up LSB MSB wrap
 *            EQ LT GT LE GE
 *            LUT digit_decomposition
 *            max exp tree_sum exp div sigmoid tanh abs
 *            send_field_data
 *            recv_field_data
 *  reduce
 */

#define print_fleld(vec)                                       \
    {                                                          \
        auto tmp_pub = field->output(nisl::PUBLIC, vec);       \
        std::cout << #vec << "_pub: " << tmp_pub << std::endl; \
    }
namespace nisl {
class FieldOp {
public:
    int party;
    IOPack* iopack;
    OTPack* otpack;
    FieldTruncation* fieldtrunc;
    BoolOp* bool_op;
    FieldOp* field;
};

}  // namespace nisl

#endif  // FIELD_OP_H__