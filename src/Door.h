#ifndef DOOR_H_
#define DOOR_H_

#include <utils/Semaphore.h>
#include "ClientsGroup.h"
#include "Fifo.h"

class Door {
private:
	Fifo doorFifo;
	Semaphore doorSemaphore;


public:
    Door();
    ClientsGroup getClients();
    void addClients(const ClientID clientID);
    void releaseFifo();
    ~Door();
};

#endif
