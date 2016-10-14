#include "Receptionist.h"
#include "LobbyMonitor.h"

Receptionist::Receptionist(Door &door) :
		door(door),
		restaurantOpen(__FILE__, 'o') {
}

int Receptionist::run() {
	for (ClientsGroup clients = door.getClients();
			clients.isValid();
			clients = door.getClients()) {
		LobbyMonitor::getInstance().addClients(clients);
	}
	return 0;
}

Receptionist::~Receptionist() {
}
