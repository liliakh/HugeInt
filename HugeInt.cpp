#include "HugeInt.h"
#include <iostream>
#include <string>
#include <vector>

using std::vector;

HugeInt::HugeInt(std::string value) {
    if (!HugeInt::isNumber(value)) {
        throw std::invalid_argument("Entered Value is not an integer");
    }
    int sz = value.size() - 1;
    for (int i = sz; i > 0; --i) {
        mValue.push_back(value[i] - '0');
    }

    if (value[0] == '-') {
        mIsNegative = true;
    }
    else {
        mValue.push_back(value[0] - '0');
    }
}

HugeInt::HugeInt(const HugeInt* arg) {
    mValue = arg->mValue;
    mIsNegative = arg->mIsNegative;
}

HugeInt::HugeInt(int value)
    : mValue(std::to_string(value)) 
      {}

HugeInt& HugeInt::operator+= (const HugeInt& arg) {
    if (mIsNegative == arg.mIsNegative) {
        mValue = HugeInt::addTwoStrings(mValue, arg.mValue);
    }
    else if (*this > arg) {
        mValue = HugeInt::subTwoStrings(mValue, arg.mValue);
    }
    else {
      mValue = HugeInt::subTwoStrings(arg.mValue, mValue);
      mIsNegative = arg.mIsNegative;
    }
    return *this;
}

HugeInt& HugeInt::operator-= (const HugeInt& arg) {
    if (mIsNegative == arg.mIsNegative) {
        if (*this > arg) {
            mValue = HugeInt::subTwoStrings(mValue, arg.mValue);
        }
        else {
            mValue = HugeInt::subTwoStrings(arg.mValue, mValue);
            mIsNegative = !mIsNegative;
        }
    }
    else if (*this > arg) {
        mValue = HugeInt::addTwoStrings(mValue, arg.mValue);
    }
    else {
        mValue = HugeInt::subTwoStrings(arg.mValue, mValue);
        mIsNegative = arg.mIsNegative;
    }

    return *this;
}

HugeInt& HugeInt::operator*= (const HugeInt& arg) {
    if (*this > arg) {
        mValue = HugeInt::multiplyTwoStrings(mValue, arg.mValue);
    }
    else {
        mValue = HugeInt::multiplyTwoStrings(arg.mValue, mValue);
    }
    mIsNegative = (mIsNegative | arg.mIsNegative);
    return *this;
}

bool HugeInt::operator> (const HugeInt& arg) {
    int length = Length();
    if (length > arg.Length()) {
        return true;
    }
    else if (length < arg.Length()) {
        return false;
    }

    for (int i = length - 1; i >= 0; --i) {
        if (int(mValue[i]) > int(arg.mValue[i])) {
            return true;
        }
        else if (int(mValue[i]) < int(arg.mValue[i])) {
            return false;
        }

    }
    return false;
}

bool HugeInt::operator< (const HugeInt& arg) {
    int length = Length();
    if (length < arg.Length()) {
        return true;
    }
    else if (length > arg.Length()) {
        return false;
    }

    for (int i = mValue.size() - 1; i >= 0; --i) {
        if (int(mValue[i]) < int(arg.mValue[i])) {
            return true;
        }
        else if (int(mValue[i]) > int(arg.mValue[i])) {
            return false;
        }
    }
    return false;
}

HugeInt HugeInt::operator+ (const HugeInt& arg) const {
    HugeInt temp(*this);
    return temp += arg;
}

HugeInt HugeInt::operator* (const HugeInt& arg) const {
    HugeInt temp(*this);
    return temp *= arg;
}

HugeInt HugeInt::operator- (const HugeInt& arg) const {
    HugeInt temp(*this);
    return temp -= arg;
}

string HugeInt::addTwoStrings(const string& s1, const std::string& s2) {
    int size1 = s1.size();
    int size2 = s2.size();
    size_t maxOfsizes = size1 >= size2 ? size1
                                       : size2;
    string resultString;
    resultString.resize(maxOfsizes);
    int carry = 0;
    for (int i = 0; i < maxOfsizes; ++i) {
        int result = 0;
        if (carry) {
            result = carry;
            carry = 0;
        }
        if (i < size1) {
            result += s1[i];
        }
        if (i < size2) {
            result += s2[i];
        }
        carry = result / 10;
        resultString[i] = result % 10;
    }
    if (carry) {
        resultString.push_back(carry);
    }

    return resultString;
}

string HugeInt::multiplyTwoStrings(const std::string& s1, const std::string& s2) {
     int size2 = s2.size();
     int currentSize = s1.size();
     string resultString;
     for (int i = 0; i < size2; ++i) {
         int k = s2[i];
         int carry = 0;
         int result = 0;
         string st;
         st.append(i, 0);

         for (int j = 0; j < currentSize; ++j) {
             result = k * s1[j] + carry;
             carry = result / 10;
             st.push_back(result % 10);
         }
         if (carry) {
             st.push_back(carry);
         }

         resultString = resultString.empty() ? st
                                             : HugeInt::addTwoStrings(st, resultString);
     }

     while (int(resultString.back() == 0)) {
         resultString.pop_back();
     }
     return resultString;
}

string HugeInt::subTwoStrings(const std::string& s1, const std::string& s2) {
    int size = s1.size();
    int debt = 0;
    std::string resultString;
    resultString.resize(size);
    for (int i = 0; i < size; ++i) {
        int res = s1[i];
        if (debt) {
            if (res) {
                --res;
                debt = 0;
            }
            else {
                res = 9;
            }
        }
        if (i > s2.size() ) {
            resultString[i] = res;
            break;
        }
        if (res - s2[i] < 0) {
            res += 10;
            debt = 1;
        }
        resultString[i] = res - s2[i];
    }
    while (int(resultString.back() == 0)) {
        resultString.pop_back();
    }

    return resultString;
}

void HugeInt::printValue() const {
    if (mIsNegative) {
        std::cout << "-";
    }
    for (int i = mValue.size() - 1; i >= 0; --i) {
        std::cout << int(mValue[i]);
    }
    std::cout << "\n";
}

bool HugeInt::isNumber(const string& str)
{
    if (!std::isdigit(str[0]) && str[0] != '-') {
        return false;
    }

    return !str.empty() &&
        std::find_if(str.begin() + 1, str.end(),
            [](unsigned char c) { return !std::isdigit(c); }) == str.end();
}