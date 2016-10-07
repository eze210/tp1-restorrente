#include "LobbyMonitor.h"
#include "LockedScope.h"


/** The instances in different processes of this class will have the
 * 	same exclusive lock, and share the same shared counters.
 */
LobbyMonitor::LobbyMonitor() :
	mutex(__FILE__ ".mutex"),
	numberOfFreeTables(__FILE__, 't'),
	numberOfClientsInLobby(__FILE__, 'c') {
}


/** Adds a client in the corresponding queue (lobby or direct queue to tables)
 */
void LobbyMonitor::addClient() {
	LockedScope l(mutex);
	numberOfClientsInLobby.write(numberOfClientsInLobby.read() + 1);
}


/** Gets a client from the corresponding queue (first wants in lobby queue
 *  and after in the direct queue)
 */
void LobbyMonitor::getClient() {
	LockedScope l(mutex);
	numberOfClientsInLobby.write(numberOfClientsInLobby.read() - 1);
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


/** There is only one instance of this class for each process where it is used.
 * 	This method returns that instance, which is destroyed with the
 * 	data segment of the process.
 */
LobbyMonitor &LobbyMonitor::getInstance() {
	static LobbyMonitor instance;
	return instance;
}
