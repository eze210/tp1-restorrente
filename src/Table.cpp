#include <domain/Order.h>
#include <processes/Waiter.h>
#include "Table.h"
#include "LobbyMonitor.h"
#include "Logger.h"

Table::Table(WaitersQueue& waitersQ) : keepAlive(true), waitersQueue(waitersQ) {
}

int Table::run() {
	while (keepAlive) {
		try {
			ClientsGroup clients = LobbyMonitor::getInstance().getClients();
			//OrderID order = clients.getOrder();
			// For calculating the cost
			uint32_t waiterID = waitersQueue.getWaiter();
			Waiter waiter(waiterID);
			LOGGER << "The clients " << clients.getID() <<
					" are in their table" << logger::endl;
			orderToWaiter(clients, waiter);
			waitForPreparedDish(clients, waiter);
			clients.eat();
			LOGGER << "The clients " << clients.getID() <<
					" are finished eating" << logger::endl;
		}
		catch (const OSException& ex){
			keepAlive = false;
		}
	}
	return 0;
}


void Table::orderToWaiter(ClientsGroup clients, Waiter& waiter) {
	LOGGER << "The clients " << clients.getID() <<
			" are served by waiter " << waiter.getID() << logger::endl;
	waiter.addOrder(clients.getID(), clients.getOrder());
	waitersQueue.addWaiter(waiter.getID());
}

void Table::waitForPreparedDish(ClientsGroup clients, Waiter& waiter) {
	LOGGER << "The clients " << clients.getID() <<
			" are waiting for the dish " << logger::endl;
	waiter.getDish(clients.getID());
	LOGGER << "The clients " << clients.getID() <<
			" are received the dish" << logger::endl;
}


Table::~Table() {
}
