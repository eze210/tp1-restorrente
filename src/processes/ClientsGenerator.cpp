#include "Door.h"
#include "ClientsGenerator.h"
#include "Logger.h"


ClientsGenerator::ClientsGenerator(ClientID clientsCount) {
	LOGGER << "Creating a clients generator" << logger::endl;
    this->clientsCount = clientsCount;
}

ClientsGenerator::~ClientsGenerator() { }

int ClientsGenerator::run() {
	LOGGER << "Starting a clients generator" << logger::endl;
    Door door;
    for (ClientID i = 0; i < clientsCount; ++i) {
    	LOGGER << "The client " << i << " has arrived to the restorrente" <<
    			logger::endl;
        door.addClients(i);
    }
    return 0;
}
