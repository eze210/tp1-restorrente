#include "LobbyMonitor.h"
#include "LockedScope.h"
#include "FifoWrite.h"
#include "FifoRead.h"
#include <string>


static const std::string lobbyFifoName("lobby.fifo");
static const std::string tableQueueFifoName("tablequeue.fifo");


/** The instances in different processes of this class will have the
 * 	same exclusive lock, and share the same shared counters.
 */
LobbyMonitor::LobbyMonitor() :
        mutex("lobby_monitor.mutex"),
        numberOfFreeTables(__FILE__, 't'),
        numberOfClientsInLobby(__FILE__, 'c'),
		lobbyFifo(lobbyFifoName),
		tableQueueFifo(tableQueueFifoName) {
}


/** Adds a client in the corresponding queue (lobby or direct queue to tables)
 */
void LobbyMonitor::addClients(const ClientsGroup &clients) {
    static FifoWrite lobbyFifo(lobbyFifoName);
    static FifoWrite tableQueueFifo(tableQueueFifoName);

	ClientID clientID = clients.getID();
    mutex.lock();
    size_t freeTables = numberOfFreeTables.read();
    if (freeTables == 0) {
        numberOfClientsInLobby.write(numberOfClientsInLobby.read() + 1);
    }
    mutex.unlock();

    if (freeTables == 0) {
        lobbyFifo.write(static_cast<const void *>(&clientID), sizeof clientID);
    } else {
        tableQueueFifo.write(static_cast<const void *>(&clientID),
                             sizeof clientID);
    }
}


/** Gets a client from the corresponding queue (first wants in lobby queue
 *  and after in the direct queue)
 */
ClientsGroup LobbyMonitor::getClients() {
    static FifoRead lobbyFifo(lobbyFifoName);
    static FifoRead tableQueueFifo(tableQueueFifoName);

	ClientID clientID;
    mutex.lock();
    size_t clientsInLobby = numberOfClientsInLobby.read();
    if (clientsInLobby > 0) {
        numberOfClientsInLobby.write(clientsInLobby - 1);
        mutex.unlock();
        lobbyFifo.read(static_cast<void *>(&clientID), sizeof clientID);
    } else {
        mutex.unlock();
        tableQueueFifo.read(static_cast<void *>(&clientID), sizeof clientID);
    }

    return ClientsGroup(clientID);
}


/** Gets the current number of clients in the lobby queue.
 */
size_t LobbyMonitor::getNumberOfClientsInLobby() {
    LockedScope l(mutex);
    return numberOfClientsInLobby.read();
}


/** When a table is free, it should take an advice to the monitor.
 */
void LobbyMonitor::increaseFreeTables() {
    LockedScope l(mutex);
    numberOfFreeTables.write(numberOfFreeTables.read() + 1);
}


/** When a table is busy, it should take an advice to the monitor.
 */
void LobbyMonitor::decreaseFreeTables() {
    LockedScope l(mutex);
    numberOfFreeTables.write(numberOfFreeTables.read() - 1);
}


/** Gets the number of free tables in the restaurant.
 */
size_t LobbyMonitor::getNumberOfFreeTables() {
    LockedScope l(mutex);
    return numberOfFreeTables.read();
}


/** Releases the fifos used by monitor.
 */
void LobbyMonitor::release() {
	lobbyFifo.release();
	tableQueueFifo.release();
	mutex.release();
}


/** There is only one instance of this class for each process where it is used.
 * 	This method returns that instance, which is destroyed with the
 * 	data segment of the process.
 */
LobbyMonitor &LobbyMonitor::getInstance() {
    static LobbyMonitor instance;
    return instance;
}
