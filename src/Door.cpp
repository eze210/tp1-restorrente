#include "Door.h"
#include "FifoWrite.h"
#include "FifoRead.h"
#include <string>
#include <data/Config.h>

/** Name to represent the fifo in the file system. */
const static std::string doorFifoName("door.fifo");
/** Name to represent the semaphore in the file system. */
const static std::string doorSemName("door.semaphore");


Door::Door() : 	doorFifo(doorFifoName),
			   	doorSemaphore(doorSemName,
			 	Config::getReceptionistsCount()) {
}

ClientsGroup Door::getClients() {
	/* fifo instance that only exists if the process uses this method */
	static FifoRead doorFifo(doorFifoName);

	doorSemaphore.p();
	/* blocks until a client id is ready to be read */
	ClientID newClientID;
    doorFifo.read(static_cast<void *>(&newClientID), sizeof newClientID);

    /* builds and returns a new instance of clients group */
    return ClientsGroup(newClientID);
}

void Door::addClients(const ClientID clientID) {
	/* fifo instance that only exists if the process uses this method */
	static FifoWrite doorFifo(doorFifoName);

	doorSemaphore.v();
	/* puts the id in the fifo */
	doorFifo.write(static_cast<const void *>(&clientID), sizeof clientID);
}

void Door::releaseFifo() {
	doorFifo.release();
}

Door::~Door() {
	doorSemaphore.erase();
}
