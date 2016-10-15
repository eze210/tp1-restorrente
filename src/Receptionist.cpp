#include "Receptionist.h"
#include "LobbyMonitor.h"
#include <unistd.h>
#include "Logger.h"

Receptionist::Receptionist(Door &door) :
door(door),
restaurantOpen(__FILE__, 'o') {
}

int Receptionist::run() {
	LOGGER << "Receptionist " << getpid() <<
			" waiting for clients in the door" << logger::endl;
	try {
		for (ClientsGroup clients = door.getClients();
				clients.isValid();
				clients = door.getClients()) {
			LOGGER << "Receptionist " << getpid() << " receiving the clients " <<
					clients.getID() << " from door, going to lobby" <<
					logger::endl;
			{
				/* NOT SYNC! just simulates time to take the clients
				 * to lobby or to table */
				sleep(1);
			}
			LobbyMonitor::getInstance().addClients(clients);

			LOGGER << "Receptionist " << getpid() <<
					" waiting for clients in the door" << logger::endl;
		}
	}
	catch (const OSException& ex) {
		LOGGER << "Receptionist " << getpid() << " saw the door closed" <<
				logger::endl;
		return 0;
	}
	return 0;
}

Receptionist::~Receptionist() {
}
