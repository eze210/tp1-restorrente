#ifndef LOBBYMONITOR_H_
#define LOBBYMONITOR_H_

#include "Mutex.h"
#include "SharedMemory.h"

class LobbyMonitor {
private:
	Mutex mutex;
	SharedMemory<size_t> numberOfFreeTables;
	SharedMemory<size_t> numberOfClientsInLobby;

	LobbyMonitor();

public:
	void addClient();
	void getClient();
	size_t getNumberOfFreeTables();
	void increaseFreeTables();
	void decreaseFreeTables();
	LobbyMonitor &getInstance();
	~LobbyMonitor();
};

#endif
