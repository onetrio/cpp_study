#include "String.hpp"

#include <iostream>

using std::cout;

const int ArSize = 10;
const int MaxLen = 81;

void callme1(String &);
void callme2(String);

int main() {
    using std::endl;
    {
        cout << "Starting an inner block.\n";
        String headline1("Celery Stalks at Midnight.");
        String headline2("Lettuce Prey.");
        String sports("Spinach Leaves Bow1 for Dollars.");

        cout << "headline1:\t" << headline1 << endl;
        cout << "headline2:\t" << headline2 << endl;
        cout << "sports:\t" << sports << endl;

        callme1(headline1);
        cout << "headline1:\t" << headline1 << endl;

        // 值传递发生调用默认的复制构造函数，属于浅拷贝
        callme2(headline2);
        cout << "headline2:\t" << headline2 << endl;

        cout << "\nInitialize one object to another:\n";
        // 可能会调用重载的赋值运算符，也可能调用复制构造函数，依赖编译器的实现
        String sailor = sports;
        cout << "sailor: " << sailor << endl;

        cout << "Assign one object to another:\n";
        String knot;
        // 将已有的对象赋值给另一个对象时，将使用重载的赋值运算符
        knot = headline1;
        cout << "knot: " << knot << endl;

        cout << "Exiting the block\n";
    }


    using std::cout;
    using std::cin;
    using std::endl;

    String name;

    cout << "Hi, what's your name?\n>> ";
    cin >> name;

    cout << name << ", please enter up to " <<
        ArSize << " short sayings <empty line to quit>:\n";

    String sayings[ArSize];
    char temp[MaxLen];
    int i;
    for (i = 0; i < ArSize; i++)
    {
        cout << i + 1 << ": ";
        cin.get(temp, MaxLen);
        while (cin && cin.get() != '\n')
        {
            continue;
        }

        if (!cin || temp[0] == '\0')
        {
            // 空行
            break;
        }
        else
        {
            sayings[i] = temp;
        }
    }

    int total = i;

    if (total > 0)
    {
        cout << "Here is your sayings:\n";
        for (int i = 0; i < total; i++)
        {
            cout << sayings[i];
        }

        int shortest = 0;
        int longest = 0;
        for (int i = 1; i < total; ++i)
        {
            if (sayings[i].length() < sayings[shortest].length())
            {
                shortest = i;
            }

            if (sayings[i].length() > sayings[longest].length())
            {
                longest = i;
            }
        }

        cout << "Your shortest saying : " << sayings[shortest] << endl;
        cout << "Your longest saying : " << sayings[longest] << endl;

        cout << "This is program used " << String::HowMany() << " String objects. Bye.\n";
    }
    else
    {
        cout << "No input! Bye.\n";
    }

    return 0;
}

void callme1(String &s)
{
    cout << "String passed by reference:\n";
    cout << "\t\"" << s << "\"\n";
}

void callme2(String s)
{
    cout << "String passed by value:\n";
    cout << "\t\"" << s << "\"\n";
}