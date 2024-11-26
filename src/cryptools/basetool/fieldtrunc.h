#ifndef FIELD_TRUNCATION_H__
#define FIELD_TRUNCATION_H__
#include "emp-ot.h"

class FieldTruncation {
public:
    int party;
    nisl::IOPack* iopack;
    nisl::OTPack* otpack;

    // Constructor
    FieldTruncation(int party, nisl::IOPack* iopack, nisl::OTPack* otpack);
    // Destructor
    ~FieldTruncation();

    void fieldtruncate();
};

#endif  // FIELD_TRUNCATION_H__