#ifndef __STRINGBAD_H__
#define __STRINGBAD_H__

#include <iostream>

class String
{
private:
    char *str;
    int len;
    static int num_strings;
    static const int CINLIM = 80;
public:
    // 函数初始化时调用构造函数，对象赋值时调用重载的赋值运算符
    String(const char *s);

    // 以下四个函数如果不定义，编译器会生成默认的定义
    // 默认的拷贝构造函数是逐个复制非静态成员，属于浅拷贝
    String(const String &s);
    String();
    ~String();
    // 如果包含动态内存分配的成员变量（指针），则应重新定义，执行深拷贝
    String &operator=(const String &);
    String &operator=(const char *);

    int length() { return len; }

    // 将比较函数作为友元，有助于将String对象和常规的C字符串进行比较
    // 例如 if("love" == answer) -> if(operator==("love", answer)) -> if(operator==(String("love"), answer))
    friend bool operator<(const String &s1, const String &s2);
    friend bool operator>(const String &s1, const String &s2);
    friend bool operator==(const String &s1, const String &s2);
    friend std::ostream &operator<<(std::ostream &os, const String &st);
    friend std::istream &operator>>(std::istream &is, String &s);

    // 表达式city[0]中，city是地一个操作数，[]是操作符，0是第二个操作数
    // city[0] -> city.operator[](0)
    char &operator[](int i);
    // 在重载时，C++将区分常量和非常量函数的特征标, 所以可以提供一个进攻const String 对象使用的operator版本。
    const char &operator[](int i) const;

    static int HowMany();
};

#endif /* __STRINGBAD_H__ */  
