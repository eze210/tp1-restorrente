#ifndef LOBBYMONITOR_H_
#define LOBBYMONITOR_H_

#include "Mutex.h"

class LobbyMonitor {
private:
	Mutex mutex;

public:
	LobbyMonitor();
	void addClient();
	void getClient();
	~LobbyMonitor();
};

#endif
