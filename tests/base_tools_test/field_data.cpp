#include <cryptools/ss/field-data.h>

int main() {
    nisl::TYPE value1 = 2 * (1ULL << nisl::FIXED_PRECISION), value2 = 3 * (1ULL << nisl::FIXED_PRECISION);
    nisl::gfpScalar x, y;
    x.set_value(value1);
    y.set_value(value2);

    // x.pow(2);
    // std::cout << x << "\n";
    // std::cout << double(x.get_value()) / (1ULL << (nisl::FIXED_PRECISION * 2)) << "\n";

    // x.sqrt();
    // std::cout << x << "\n";
    // std::cout << double(x.get_value()) / (1ULL << nisl::FIXED_PRECISION) << "\n";

    nisl::gfpScalar ret = x / y;  // ???
    std::cout << ret << "\n";
    std::cout << double(ret.get_value()) / (1ULL << nisl::FIXED_PRECISION) << "\n";
}