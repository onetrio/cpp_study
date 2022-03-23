#include <iostream>

using namespace std;

void other();
void another(); // 是否可以直接访问？

int x = 10;
int y;

int main()
{
    cout << x << endl; // 10

    {
        int x = 4; // 会隐藏全局变量 x

        cout << x << endl; // 4
        cout << y << endl; // 0, 全局变量会被编译器设置为 0
    }

    other(); // Other： 10, 1
    another();

    return 0;
}

void other() {
    int y = 1; // 会隐藏全局变量 y
    cout << "Other： " << x << ", " << y << endl; // x = 10, y = 1
}
