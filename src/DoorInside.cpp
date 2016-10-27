//
// Created by fabrizio on 26/10/16.
//

#include <string>
#include "DoorInside.h"


/** Name to represent the fifo in the file system. */
const static std::string doorFifoName("door.fifo");

DoorInside::DoorInside() : 	doorFifo(doorFifoName){
}

ClientsGroup DoorInside::getClients() {
    /* blocks until a client id is ready to be read */
    ClientID newClientID;
    doorFifo.read(static_cast<void *>(&newClientID), sizeof newClientID);
    /* builds and returns a new instance of clients group */
    return ClientsGroup(newClientID);
}

void DoorInside::releaseFifo() {
    doorFifo.release();
}

DoorInside::~DoorInside() {
}
