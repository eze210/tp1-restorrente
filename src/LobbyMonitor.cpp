#include "LobbyMonitor.h"
#include "LockedScope.h"

LobbyMonitor::LobbyMonitor() :
	mutex(__FILE__ ".mutex"),
	numberOfFreeTables(__FILE__, 't'),
	numberOfClientsInLobby(__FILE__, 'c') {
}

void LobbyMonitor::addClient() {
	LockedScope l(mutex);
	numberOfClientsInLobby.write(numberOfClientsInLobby.read() + 1);
}

void LobbyMonitor::getClient() {
	LockedScope l(mutex);
	numberOfClientsInLobby.write(numberOfClientsInLobby.read() - 1);
}

void LobbyMonitor::increaseFreeTables() {
	LockedScope l(mutex);
	numberOfFreeTables.write(numberOfFreeTables.read() + 1);
}

void LobbyMonitor::decreaseFreeTables() {
	LockedScope l(mutex);
	numberOfFreeTables.write(numberOfFreeTables.read() - 1);
}

size_t LobbyMonitor::getNumberOfFreeTables() {
	LockedScope l(mutex);
	return numberOfFreeTables.read();
}

LobbyMonitor &LobbyMonitor::getInstance() {
	static LobbyMonitor instance;
	return instance;
}

LobbyMonitor::~LobbyMonitor() {
}
