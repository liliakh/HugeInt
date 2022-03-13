#include "HugeInt.h"

#include <iostream>

int main()
{
    try {
        HugeInt a(std::string("-39652108745"));
        HugeInt b(std::string("1478965224156326988"));
        HugeInt d(std::string("9854711425789136541"));
        HugeInt c = (a + b);
        a += d;
        b -= d;
        d *= a;
        a.printValue();
        c.printValue();
        b.printValue();
        d.printValue();

    }
    catch (std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
