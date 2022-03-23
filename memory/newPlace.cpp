#include <iostream>
#include <new>

using namespace std;

const int BUF = 512;
const int N = 5;
char buffer[BUF];

int main()
{
    double *pd1, *pd2;
    int i;

    cout << "Calling new and placement new:\n";

    pd1 = new double[N];

    // 将会把buffer的区域分配给pd2
    pd2 = new (buffer)double[N];

    cout << "placement new pd2 = " << pd2 << "; buffer = " << (void *)buffer << endl;

    for (i = 0; i < N; i++)
    {
        pd1[i] = pd2[i] = 1000 * 20.0 * i;
    }

    for (i = 0; i < N; i++)
    {
        cout << "new pd1[" << i << "] at " << &pd1[i] << "; ";
        cout << "placement new pd2[" << i << "] at " << &pd2[i] << endl;
    }

    // pd1所指向的内存是从堆上分配的，所以需要delete。
    delete pd1;
    // pd2所指向的内存是在全局变量区，不能delete，delete会导致段错误
    // delete pd2;

    return 0;
}