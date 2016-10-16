//
// Created by fabrizio on 15/10/16.
//

#ifndef RESTORRENTE_KITCHEN_H
#define RESTORRENTE_KITCHEN_H


#include <domain/Order.h>
#include <sched.h>
#include <vector>
#include <utils/Mutex.h>
#include <utils/MyProcess.h>

using std::pair;
using std::vector;

class Kitchen : public MyProcess {
public:
    Kitchen();
    ~Kitchen();
    int run();
    void prepareOrder(OrderID order);
private:
    vector<OrderID> orders;
    Mutex mutex;
};


#endif //RESTORRENTE_KITCHEN_H
