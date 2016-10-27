#ifndef DOOR_H_
#define DOOR_H_

#include <utils/Semaphore.h>
#include <utils/Fifos/FifoWrite.h>
#include "ClientsGroup.h"
#include "Fifo.h"

class DoorOutside {
private:
	FifoWrite doorFifo;

public:
    DoorOutside();
    void addClients(const ClientID clientID);
    void releaseFifo();
    ~DoorOutside();
};

#endif
