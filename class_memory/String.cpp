#include "String.hpp"
#include <cstring>

int String::num_strings = 0;

String::String(const char *s) {
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    num_strings++;
}

String::String(const String &s)
{
    len = s.len;
    str = new char[len + 1];
    std::strcpy(str, s.str);
    num_strings++;
}

String::String() {
    len = 0;
    str = new char[len + 1];
    std::strcpy(str, "");
    num_strings++;
}

String::~String() {
    --num_strings;
    delete[] str;
}

// 返回一个对象引用是为了实现 S1 = S2 = S3， 即S1.operator(S2.operator(S3))
String &String::operator=(const String &sb)
{
    // 函数应该避免将对象赋值给本身，否则，给对象重新赋值前，释放内存操作可能会删除对象的内容。
    if (this == &sb)
    {
        return *this;
    }

    // 对象之前可能包含内容，需要进行释放，否则可能导致内存泄漏
    delete[] str;

    len = sb.len;
    str = new char[len + 1];
    std::strcpy(str, sb.str);

    return *this;
}

// 提高常规字符串赋值的效率
String &String::operator=(const char *s)
{
    delete[] str;
    len = std::strlen(s);
    str = new char[len + 1];
    std::strcpy(str, s);
    return *this;
}

bool operator<(const String &s1, const String &s2)
{
    if (std::strcmp(s1.str, s2.str) < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator>(const String &s1, const String &s2)
{
    if (std::strcmp(s1.str, s2.str) > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator==(const String &s1, const String &s2)
{
    if (std::strcmp(s1.str, s2.str) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const String &st) {
    os << st.str;
    return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
    char temp[String::CINLIM];
    is.get(temp, String::CINLIM);
    // 由于某种原因，如达到文件尾，或者读取的是一个空行，istream的对象的值将设置为false。
    if (is)
    {
        s = temp;
    }

    // 丢弃多余的字符
    while (is && is.get() != '\n')
        continue;

    return is;

}


char &String::operator[](int i)
{
    return str[i];
}

const char &String::operator[](int i) const
{
    return str[i];
}

int String::HowMany()
{
    return num_strings;
}