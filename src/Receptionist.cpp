#include "Receptionist.h"

Receptionist::Receptionist(Door &door, LobbyMonitor &lobbyMonitor) :
	door(door),
	lobbyMonitor(lobbyMonitor) {
}

int Receptionist::run() {
	while (true) {
		lobbyMonitor.addClients(door.getClients());
	}
	return 0;
}

Receptionist::~Receptionist() {
}

