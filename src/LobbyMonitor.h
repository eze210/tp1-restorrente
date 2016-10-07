#ifndef LOBBYMONITOR_H_
#define LOBBYMONITOR_H_

#include "Mutex.h"
#include "SharedMemory.h"
#include "ClientsGroup.h"

class LobbyMonitor {
private:
	/** Exclusive lock. */
	Mutex mutex;
	/** Shared counters. */
	SharedMemory<size_t> numberOfFreeTables;
	SharedMemory<size_t> numberOfClientsInLobby;
	/** Queue to tables (without enter to lobby) */

	/** Lobby queue */

	LobbyMonitor();

public:
	size_t getNumberOfClientsInLobby();
	void addClients(const ClientsGroup &clients);
	ClientsGroup getClients();

	size_t getNumberOfFreeTables();
	void increaseFreeTables();
	void decreaseFreeTables();

	static LobbyMonitor &getInstance();
};

#endif
