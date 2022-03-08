#include "HugeInt.h"

#include <iostream>

int main()
{
    try {
        HugeInt a(std::string("983514785412366227"));
        HugeInt b(std::string("23452165"));
        HugeInt c = a * b;
        HugeInt d(125);
        d += a;

        c.printValue();
        d.printValue();

    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
