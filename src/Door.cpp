#include "Door.h"
#include "FifoWrite.h"
#include "FifoRead.h"
#include <string>

const static std::string doorFifoName("door.fifo");

Door::Door() {
}

ClientsGroup Door::getClients() {
	static FifoRead doorFifo(doorFifoName);
	ClientsGroup clients(0);
	doorFifo.read(static_cast<void*>(&clients), sizeof clients);
	return clients;
}

void Door::addClients(ClientsGroup &clients) {
	static FifoWrite doorFifo(doorFifoName);
	doorFifo.write(static_cast<const void*>(&clients), sizeof clients);
}

Door::~Door() {
}

