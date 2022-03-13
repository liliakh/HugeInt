#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
using std::string;

class HugeInt
{
public:
     HugeInt(std::string value = "");
     HugeInt(int value);
     HugeInt(const HugeInt* arg);

     HugeInt& operator+= (const HugeInt & arg);
     HugeInt& operator*= (const HugeInt& arg);
     HugeInt& operator-= (const HugeInt& arg);

     bool operator> (const HugeInt& arg);
     bool operator< (const HugeInt& arg);

     HugeInt operator + (const HugeInt & arg) const;
     HugeInt operator * (const HugeInt & arg) const;
     HugeInt operator - (const HugeInt& arg) const;

     size_t Length() const { return mValue.size(); }
     void printValue() const;

     static string addTwoStrings(const string& s1, const std::string& s2);
     static string multiplyTwoStrings(const std::string& s1, const std::string& s2);
     static string subTwoStrings(const string& s1, const std::string& s2);
    
     bool isNumber(const string& str);

private:
     std::string mValue = "";
     bool mIsNegative = false;
};

#endif // HUGEINT_H
