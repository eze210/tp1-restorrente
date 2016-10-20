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
#include "LockFile.h"

using std::pair;
using std::vector;

class Kitchen  {
public:
    //Kitchen();
    Kitchen(LockFile& lock);
    ~Kitchen();
    int run();
    void prepareOrder(OrderID order);
    OrderID getPreparedOrder();
private:
    vector<OrderID> orders;
    LockFile& mutex;
};


#endif //RESTORRENTE_KITCHEN_H
