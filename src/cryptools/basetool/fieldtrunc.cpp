#include "fieldtrunc.h"

using namespace std;
using namespace nisl;

FieldTruncation::FieldTruncation(int party, IOPack* iopack, OTPack* otpack) {
    this->party  = party;
    this->iopack = iopack;
    this->otpack = otpack;
}

FieldTruncation::~FieldTruncation() {}

void FieldTruncation::fieldtruncate() {}