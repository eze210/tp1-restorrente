#include "Receptionist.h"
#include "LobbyMonitor.h"
#include <unistd.h>
#include "Logger.h"


Receptionist::Receptionist(Door &door) :
		door(door),
		restaurantOpen(__FILE__, 'o') {
}

int Receptionist::run() {
	LOGGER << "Waiting for clients in the door" << logger::endl;
	for (ClientsGroup clients = door.getClients();
			clients.isValid();
			clients = door.getClients()) {
		LOGGER << "Receiving a client from door, going to lobby" <<
				logger::endl;
		{
			/* NOT SYNC! just simulates time to take the clients
			 * to lobby or to table */
			sleep(1);
		}
		LobbyMonitor::getInstance().addClients(clients);

		LOGGER << "Waiting for clients in the door" << logger::endl;
	}
	return 0;
}

Receptionist::~Receptionist() {
}
