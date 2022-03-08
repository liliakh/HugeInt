#ifndef HUGEINT_H
#define HUGEINT_H

#include <iostream>
using std::string;

class HugeInt
{
public:
     HugeInt(std::string value = "");
     HugeInt(int value);
     HugeInt(const HugeInt* other);

     HugeInt operator+= (const HugeInt & arg);
     HugeInt operator*= (const HugeInt& arg);

     HugeInt operator + (const HugeInt & arg) const;
     HugeInt operator * (const HugeInt & arg) const;

     size_t Length() const { return mValue.size(); }
     void printValue() const;

     static std::string addTwoStrings(std::string, std::string);
     static bool isNumber(const string& str);

private:
     std::string mValue = "";
};


#endif // HUGEINT_H
