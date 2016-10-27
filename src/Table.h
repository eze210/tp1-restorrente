#ifndef TABLE_H_
#define TABLE_H_

#include "ClientsGroup.h"
#include "MyProcess.h"
#include "WaitersQueue.h"
#include "Waiter.h"
#include "Kitchen.h"

class Table : public MyProcess {
private:
    bool keepAlive;
    WaitersQueue& waitersQueue;
    Kitchen& kitchen;
    int orderToSomeWaiter(ClientsGroup &clients);
    void waitForPreparedDish(ClientsGroup &clients);
    void pay(int price);

public:
    Table(WaitersQueue& waitersQueue, Kitchen& theKitchen);
    int run();
    ~Table();
};

#endif
