#include "HugeInt.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;

HugeInt::HugeInt(std::string value) {
    if (!HugeInt::isNumber(value)) {
        throw std::invalid_argument("Entered Value is not a positive integer");
    }
    int sz = value.size() - 1;
    for (int i = sz; i >= 0; --i) {
        mValue.push_back(value[i] - '0');
    }
}

HugeInt::HugeInt(const HugeInt* other) {
    mValue = other->mValue;
}

HugeInt::HugeInt(int value)
    :mValue(std::to_string(value)) {}

HugeInt HugeInt::operator+= (const HugeInt& arg) {
    mValue = HugeInt::addTwoStrings(mValue, arg.mValue);

    return *this;
}

HugeInt HugeInt::operator*= (const HugeInt& arg) {
    std::string other = arg.mValue;
    int sz = other.size();
    if (sz > mValue.size()) {
        mValue.resize(sz* mValue.size());
    }

    int currentSize = mValue.size();

    string resultString;
    for (int i = 0; i < sz; ++i) {
        int k = other[i];
        int carry = 0;
        int result = 0;
        string st;
        st.append(i, 0);

        for (int j = 0; j < currentSize; ++j) {
            result = k * mValue[j] + carry;
            carry = result / 10;
            st.push_back(result % 10);
        }
        if (carry) {
            st.push_back(carry);
        }

        resultString = resultString.empty() ? st
            : HugeInt::addTwoStrings(st, resultString);
    }

    mValue = resultString;

    return *this;
}

HugeInt HugeInt::operator+ (const HugeInt& arg) const {
    HugeInt temp(*this);
    return temp += arg;
}

HugeInt HugeInt::operator* (const HugeInt& arg) const {
    HugeInt temp(*this);
    return temp *= arg;
}

string HugeInt::addTwoStrings(std::string s1, std::string s2) {
    int size2 = s2.size();
    if (size2 > s1.size()) {
        s1.resize(size2);
    }

    int size1 = s1.size();
    int carry = 0;
    int result = 0;
    for (int i = 0; i < size1; ++i) {
        result = (i < size2) ? s1[i] + s2[i] + carry
            : s1[i] + carry;
        carry = result / 10;
        s1[i] = result % 10;
    }
    if (carry) {
        s1.push_back(carry);
    }

    return s1;
}

void HugeInt::printValue() const {
    for (int i = mValue.size() - 1; i >= 0; --i) {
        std::cout << int(mValue[i]);
    }
    std::cout << "\n";
}

bool HugeInt::isNumber(const string& str)
{
    return !str.empty() &&
        std::find_if(str.begin(), str.end(),
            [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}