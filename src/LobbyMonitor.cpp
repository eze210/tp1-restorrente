#include "LobbyMonitor.h"
#include "LockedScope.h"

LobbyMonitor::LobbyMonitor() : mutex(__FILE__ ".mutex") {
}

void LobbyMonitor::addClient() {
	LockedScope l(mutex);
}

void LobbyMonitor::getClient() {
	LockedScope l(mutex);
}

LobbyMonitor::~LobbyMonitor() {
}

