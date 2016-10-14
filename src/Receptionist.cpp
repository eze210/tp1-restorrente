#include "Receptionist.h"
#include "LobbyMonitor.h"
#include <iostream>

Receptionist::Receptionist(Door &door) :
		door(door),
		restaurantOpen(__FILE__, 'o') {
}

int Receptionist::run() {
	for (ClientsGroup clients = door.getClients();
			clients.isValid();
			clients = door.getClients()) {
		std::cout << "adding a client to lobby" << std::endl;
		LobbyMonitor::getInstance().addClients(clients);
		std::cout << "added a client to lobby" << std::endl;
	}
	return 0;
}

Receptionist::~Receptionist() {
}
