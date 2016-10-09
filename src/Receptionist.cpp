#include "Receptionist.h"

Receptionist::Receptionist(Door &door, LobbyMonitor &lobbyMonitor) :
        door(door),
        lobbyMonitor(lobbyMonitor) {
}

int Receptionist::run() {
    ClientsGroup clients = door.getClients();
    while (clients.notNull()) {
        lobbyMonitor.addClients(clients);
        clients = door.getClients();
        std::cout << clients.notNull() << std::endl;
    }
    return 0;
}

Receptionist::~Receptionist() {
}

