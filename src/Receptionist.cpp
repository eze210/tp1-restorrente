#include "Receptionist.h"
#include "LobbyMonitor.h"
#include <unistd.h>
#include <data/Config.h>
#include "Logger.h"

/** Name to represent the semaphore in the file system. */
const static std::string doorSemName("door.semaphore");

Receptionist::Receptionist(DoorInside& aDoor) :
door(aDoor),
doorSemaphore(doorSemName, Config::getReceptionistsCount()){
	LOGGER << "Creating receptionist " << getpid() << logger::endl;
}

int Receptionist::run() {
	LobbyMonitor::getInstance().openForWrite();
	LOGGER << "Receptionist " << getpid() <<
			" waiting for clients in the door" << logger::endl;

	try {
		ClientsGroup clients(0);
		do {
			doorSemaphore.p();
			clients = door.getClients();

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
			doorSemaphore.v();
		} while (clients.isValid());
	}
	catch (const OSException& ex) {
		LOGGER << "Receptionist " << getpid() << " saw the door closed" <<
				logger::endl;
	}

	return 0;
}

Receptionist::~Receptionist() {
	doorSemaphore.erase();
}
