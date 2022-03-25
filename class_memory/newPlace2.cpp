#include <iostream>
#include <string>
#include <new>

using namespace std;

const int BUF = 512;

class JustTesting
{
private:
    string words;
    int number;

public:
    JustTesting(const string &s = "Just Testing", int n = 0) {
        words = s;
        number = n;
        cout << words << " construct\n";
    }

    ~JustTesting() {
        cout << words << " destoryed\n";
    }

    void Show() const { cout << words << ", " << number << endl; }
};

int main()
{
    char *buffer = new char[BUF];
    JustTesting *pc1, *pc2;

    pc1 = new (buffer)JustTesting();
    pc2 = new JustTesting("heap1", 20);

    cout << "Memory block addresses : \n"
        << "buffer: " << (void *)buffer << "\t heap: " << pc2 << endl;

    cout << "Memory contents:\n";
    cout << pc1 << ": ";
    pc1->Show();

    cout << pc2 << ": ";
    pc2->Show();

    JustTesting *pc3, *pc4;
    // 会覆盖pc1
    // pc3 = new (buffer)JustTesting("Bad Idea", 6);
    // fix : 指定其他位置、
    pc3 = new (buffer + sizeof(JustTesting))JustTesting("Better Idea", 6);
    pc4 = new JustTesting("Heap2", 10);

    cout << "Memory contents:\n";
    cout << pc3 << ": ";
    pc3->Show();

    cout << pc4 << ": ";
    pc4->Show();

    delete pc2;
    pc2 = nullptr;
    delete pc4;
    pc4 = nullptr;

    // pc1、pc3的析够函数函数不会被调用，所以有可能存在内存泄漏

    // 会造成段错误，因为pc1是buffer的地址，delete和new[]不匹配
    // pc3 的地址内容不是从new返回的，delete会造成未定义的行为
    // delete pc1;
    // delete pc3;
    // fix 显式调用析构函数
    pc1->~JustTesting();
    pc3->~JustTesting();

    delete[] buffer;
    buffer = nullptr;
}