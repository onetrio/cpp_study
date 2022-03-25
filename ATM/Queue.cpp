#include "Queue.hpp"

Queue::Queue(int qs = Q_SIZE)
    :qsize(qs), front(nullptr), rear(nullptr), items(0) {
}

Queue::~Queue() {
    Node *temp;
    while (front != nullptr)
    {
        temp = front;
        front = front->next;
        delete temp;
    }
}

bool Queue::isEmpty() const {
    return items == 0;
}

bool Queue::isFull() const {
    return items >= qsize;
}

int Queue::queuecount() const {
    return items;
}

bool Queue::enqueue(const Item &item) {
    if (isFull())
    {
        return false;
    }

    // new 失败会报异常
    Node *node = new Node;
    // 赋值构造函数
    node->item = item;
    node->next = nullptr;
    
    if (front == nullptr)
    {
        front = node;
    }
    else
    {
        rear->next = node;
    }
    rear = node;
    items++;

    return true;
}

bool Queue::dequeue(Item &item) {
    if (isEmpty())
    {
        return false;
    }

    items--;
    Node *node = front;
    item = node->item;
    front = node->next;
    delete node;

    if (items == 0)
    {
        rear = nullptr;
    }
}