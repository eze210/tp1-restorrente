#include "Table.h"

#include "Order.h"
#include "Waiter.h"
#include "SignalHandler.h"
#include "Config.h"
#include "LobbyMonitor.h"
#include "Logger.h"
#include "Kitchen.h"
#include "CashRegister.h"
#include <iostream>
#include "LightHandler.h"
#include "SignalHandler.h"


#define SIGNAL_KILL 2

Table::Table(WaitersQueue& waitersQ, Kitchen& theKitchen) :
		keepAlive(true), waitersQueue(waitersQ), kitchen(theKitchen) {
}

int Table::run() {
	bool powerFailure = false;
	LobbyMonitor::getInstance().openForRead();
	LightHandler lightHandler(powerFailure);
	SignalHandler::getInstance().registerHandler(
			SIGINT,
			&lightHandler);

	while (keepAlive) {
		try {
			powerFailure = false;
			ClientsGroup clients = LobbyMonitor::getInstance().getClients();

			LOGGER << "The clients " << clients.getID() <<
			" are in their table" << logger::endl;

			int allOrdersPrice = 0;
			do {
				if (powerFailure) break;
				allOrdersPrice += orderToSomeWaiter(clients);

				if (powerFailure) break;
				clients.eat();
			} while (clients.hungry() && !powerFailure);

			if (powerFailure) {
				LOGGER << "Power failure, client " << clients.getID() <<
						" did not pay and exited from the table." <<
						logger::endl;
				continue;
			}

			LOGGER << "The clients " << clients.getID() <<
			" are finished eating" << logger::endl;
			pay(allOrdersPrice);
		}
		catch (const OSException &ex) {
			keepAlive = false;
		}
	}
	return 0;
}


int Table::orderToSomeWaiter(ClientsGroup &clients) {
	/* takes a waiter from the "waiters queue" */
	Waiter waiter(kitchen, waitersQueue);

	LOGGER << "The clients " << clients.getID() <<
			" are served by some waiter" << logger::endl;

	return waiter.addOrder(clients.getID(), clients.getOrder());
	/* after return, the Waiter instance finishes its scope, and frees a
	 * waiter from queue */
}

void Table::pay(int price) {
	CashRegister::getInstance().addPayment(price);
}

Table::~Table() {
}
