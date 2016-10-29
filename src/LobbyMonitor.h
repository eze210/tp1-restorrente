#ifndef LOBBYMONITOR_H_
#define LOBBYMONITOR_H_

#include "Mutex.h"
#include "SharedMemory.h"
#include "domain/ClientsGroup.h"
#include "Fifo.h"
#include "FifoWrite.h"
#include "FifoRead.h"

class LobbyMonitor {
private:
    /** Exclusive lock. */
    Mutex mutex;
    /** Shared counters. */
    SharedMemory<size_t> numberOfFreeTables;
    SharedMemory<size_t> numberOfClientsInLobby;

    /** Queue to tables (without enter to lobby) */
    Fifo lobbyFifo;
    /** Lobby queue */
    Fifo tableQueueFifo;

    FifoWrite *lobbyFifoW;
   	FifoWrite *tableQueueFifoW;
    FifoRead *lobbyFifoR;
    FifoRead *tableQueueFifoR;

    LobbyMonitor();
    bool alive;

public:
    size_t getNumberOfClientsInLobby();
    void addClients(const ClientsGroup &clients);
    ClientsGroup getClients();
    size_t getNumberOfFreeTables();
    void increaseFreeTables();
    void decreaseFreeTables();
    void release();
    static LobbyMonitor &getInstance();
    void clear();
    bool isAlive();

    void openForWrite();
    void openForRead();

	void closeFifoWrite();

	void init() {
		numberOfClientsInLobby.write(0);
		numberOfClientsInLobby.write(0);
	}

    ~LobbyMonitor();
};

#endif
