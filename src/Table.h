#ifndef TABLE_H_
#define TABLE_H_

#include <domain/ClientsGroup.h>
#include <utils/Mutex.h>
#include <utils/LockFile.h>
#include "MyProcess.h"
#include "WaitersQueue.h"
#include "Waiter.h"
#include "Kitchen.h"

class Table : public MyProcess {
private:
    bool keepAlive;
    WaitersQueue& waitersQueue;
    Kitchen& kitchen;
    void orderToWaiter(ClientsGroup clients, Waiter& waiter);
    void waitForPreparedDish(ClientsGroup clients, Waiter& waiter);
public:
    explicit Table(WaitersQueue& waitersQueue, Kitchen& theKitchen);
    int run();
    ~Table();
};

#endif
