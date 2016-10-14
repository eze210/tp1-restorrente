#include <Door.h>
#include <data/Config.h>
#include <vector>
#include "ClientsGenerator.h"

#define CLIENTS_COUNT 10

ClientsGenerator::ClientsGenerator() { }

ClientsGenerator::~ClientsGenerator() { }

int ClientsGenerator::run() {
    Door door;
    for (ClientID i = 0; i < CLIENTS_COUNT; ++i) {
        door.addClients(i);
    }
    door.addClients(ClientsGroup::invalidClientID);
    return 0;
}
