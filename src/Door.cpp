#include "Door.h"
#include "FifoWrite.h"
#include "FifoRead.h"
#include <string>

/** Name to represent the fifo in the file system. */
const static std::string doorFifoName("door.fifo");

Door::Door() {
}

ClientsGroup Door::getClients() {
	/* fifo instance that only exists if the process uses this method */
	static FifoRead doorFifo(doorFifoName);

	/* blocks until a client id is ready to be read */
	uint32_t newClientID;
    doorFifo.read(static_cast<void *>(&newClientID), sizeof newClientID);

    /* builds and returns a new instance of clients group */
    return ClientsGroup(newClientID);
}

void Door::addClients(const uint32_t clientID) {
	/* fifo instance that only exists if the process uses this method */
	static FifoWrite doorFifo(doorFifoName);

	/* puts the id in the fifo */
	doorFifo.write(static_cast<const void *>(&clientID), sizeof clientID);
}

Door::~Door() {
}
