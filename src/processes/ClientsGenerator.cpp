#include "Door.h"
#include "ClientsGenerator.h"
#include "Logger.h"

#define CLIENTS_COUNT 10

ClientsGenerator::ClientsGenerator() { }

ClientsGenerator::~ClientsGenerator() { }

int ClientsGenerator::run() {
	LOGGER << "Starting a clients generator" << logger::endl;
    Door door;
    for (ClientID i = 0; i < CLIENTS_COUNT; ++i) {
    	LOGGER << "The client " << i << " has arrived to the restorrente" <<
    			logger::endl;
        door.addClients(i);
    }
    return 0;
}
