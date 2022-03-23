#include <iostream>

using namespace std;
extern int x;

// 未命名的名称空间， 就像后面跟着 using 编译指令一样，不能在未命名空间所属文件之外的其他文件中使用该命名空间中的名称。
// 这提供了链接性为内部的静态变量的替代品。
// static int y = -3;
namespace
{
    int y = -4;
}

void another() {
    cout << "Another： " << x << ", " << y << endl; // x = 10, y = -4
}