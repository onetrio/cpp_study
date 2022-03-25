#ifndef __QUEUE_H__
#define __QUEUE_H__
#include "Customer.hpp"

typedef Customer Item;

class Queue
{
private:
    // 在类中嵌套结构或类声明，作用域为整个类
    struct Node { Item item; Node *next; };
    enum {
        Q_SIZE = 10
    };

    // 指向队列头
    Node *front;
    // 指向队列尾
    Node *rear;
    // 当前队列长度
    int items;
    /**
     * @brief 队列的最大长度限制
     * const常量，或者引用，只能在定义时初始化，不能被赋值，而构造函数的函数体是在类给成员变量分配内存之后调用的，
     * 所以只能使用初始化函数列表const常量赋值
     */
    const int qsize;

public:
    Queue(int qs = Q_SIZE);
    ~Queue();

    bool isEmpty() const;
    bool isFull() const;
    int queuecount() const;
    bool enqueue(const Item &item);
    bool dequeue(Item &item);

private:
    // 禁止默认构造和赋值
    Queue(const Queue &) : qsize(0) {}
    Queue &operator=(const Queue &) {}
};

#endif /* __QUEUE_H__ */