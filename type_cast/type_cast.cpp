#include <iostream>

using namespace std;

class Base {
public:
    virtual void printName() {
        cout << "Base::printName()" << endl;
    }

    void baseFunc() {
        cout << "Base::baseFunc()" << endl;
    }
};

class ChildA : public Base {
    int a;
public:

    ChildA() : Base(), a(1) {}

    void printName() {
        cout << "ChildA::printName()" << endl;
    }

    void childAFunc1() {
        cout << "ChildA::childAFunc()" << endl;
    }

    void childAFunc2() {
        cout << "ChildA::childAFunc(), a = " << a << endl;
    }
};

class ChildB : public Base {
public:
    void printName() {
        cout << "ClildB::printName()" << endl;
    }
};

int main() {
    //upcast
    Base base;
    ChildA a;
    ChildB b;

    // 野指针是指未初始化的指针，加-Wall选项进行编译时，会提示 used uninitialized。
    // int *wild;
    // *wild = 1;

    // 悬空指针是指指针最初指向的内存区域已经被释放了的一种指针。
    int *dandling = new int(1);
    delete dandling;

    Base *pA = dynamic_cast<Base *>(&a);
    Base *pB = dynamic_cast<Base *>(&b);

    pA->printName();
    pB->printName();

    // pB实际指向的对象的类型是ChildB，将其转为ChildA的指针，非法，调用虚函数会崩溃
    ChildA *pcA = dynamic_cast<ChildA *>(pB);
    if (pcA == NULL)
    {
        cout << "this is not safe cast." << endl;
    }
    else
    {
        cout << "this is safe cast." << endl;
    }

    // 安全
    pcA = dynamic_cast<ChildA *>(pA);
    if (pcA == NULL)
    {
        cout << "this is not safe cast." << endl;
    }
    else
    {
        cout << "this is safe cast." << endl;
    }


    // const_cast
    const int number = 100;
    int *pInt = const_cast<int *>(&number);
    *pInt = 90;
    cout << "*pInt = " << *pInt << " number = " << number << endl; // *pInt = 90 number = 100, 因为编译期间，number会被100替代，类似于 #define

    return 0;
}