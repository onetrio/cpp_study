#include <iostream>

namespace Jack {
    double bucket(double d) {
        return d * 20;
    }

    double fetch;
}

namespace Jill {
    double bucket(double d) {
        return d * 10;
    }

    double fetch;

}

double bucket(double d) {
    return d;
}

// 如果全局有同名变量，会导致二义性
// using Jack::bucket;

int main() {
    std::cout << Jack::bucket(20) << std::endl;
    std::cout << Jill::bucket(20) << std::endl;

    // 将Jack::bucket 加入到全局命名空间, 会覆盖之前定义的同名函数
    // using Jack::bucket;
    std::cout << bucket(20) << std::endl;

    // using namespace Jill; // 导入所有的命名空间名字
    

    return 0;
}