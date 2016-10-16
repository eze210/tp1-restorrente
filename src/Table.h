#ifndef TABLE_H_
#define TABLE_H_

#include <domain/ClientsGroup.h>
#include "MyProcess.h"
#include "WaitersQueue.h"
#include "Waiter.h"

class Table : public MyProcess {
private:
    bool keepAlive;
    WaitersQueue waitersQueue;
    void orderToWaiter(ClientsGroup clients, Waiter& waiter);
    void waitForPreparedDish(ClientsGroup clients, Waiter& waiter);
public:
    explicit Table(WaitersQueue& waitersQueue);
    int run();
    ~Table();
};

#endif
