#ifndef __CUSTOMER_H__
#define __CUSTOMER_H__

#include <random>

class Customer {
private:
    long arrive;
    long processtime;
public:
    Customer() { arrive = processtime = 0; }
    void set(long when) {
        processtime = std::rand() % 3 + 1; 
        arrive = when;
    }
    long when() const { return arrive; }
    long ptime() const { return processtime; }
};

#endif /* __CUSTOMER_H__ */