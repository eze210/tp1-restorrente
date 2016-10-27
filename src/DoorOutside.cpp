#include "DoorOutside.h"

#include "FifoWrite.h"
#include "Config.h"

#include <string>

/** Name to represent the fifo in the file system. */
const static std::string doorFifoName("door.fifo");

DoorOutside::DoorOutside() : 	doorFifo(doorFifoName){
}

void DoorOutside::addClients(const ClientID clientID) {
	/* puts the id in the fifo */
	doorFifo.write(static_cast<const void *>(&clientID), sizeof clientID);
}

void DoorOutside::releaseFifo() {
	doorFifo.release();
}

DoorOutside::~DoorOutside() {
}
