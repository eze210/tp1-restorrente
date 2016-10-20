#include <domain/Order.h>
#include <processes/Waiter.h>
#include <utils/SignalHandler.h>
#include <data/Config.h>
#include "Table.h"
#include "LobbyMonitor.h"
#include "Logger.h"
#include "Kitchen.h"
#include "event_handlers/TableKillHandler.h"

#define SIGNAL_KILL 2
const static std::string cajaMem("caja.mem");
const static std::string noCobradoMem("no-cobrado.mem");
const static std::string cajaMutexName("caja.mutex");
const static std::string noCobradoMutexName("no-cobrado.mutex");

Table::Table(WaitersQueue& waitersQ, Kitchen& theKitchen) :
		keepAlive(true), waitersQueue(waitersQ), kitchen(theKitchen) {
	SignalHandler::getInstance().registerHandler(SIGINT, &handler);
	caja.create(cajaMem,1);
	dineroPorCobrar.create(noCobradoMem,2);
}

int Table::run() {
	while (keepAlive) {
		try {
			ClientsGroup clients = LobbyMonitor::getInstance().getClients();
			LobbyMonitor::getInstance().decreaseFreeTables();
			//OrderID order = clients.getOrder();
			// For calculating the cost
			uint32_t waiterID = waitersQueue.getWaiter();
			Waiter waiter(waiterID, kitchen);
			LOGGER << "The clients " << clients.getID() <<
					" are in their table" << logger::endl;
			int costoDePlato = Config::getAvailableFoods().at(clients.getOrder()).getCost();
			orderToWaiter(clients, waiter);

			int noCobrado = dineroPorCobrar.read();
			dineroPorCobrar.write(noCobrado + costoDePlato);

			waitForPreparedDish(clients, waiter);
			clients.eat();
			LOGGER << "The clients " << clients.getID() <<
					" are finished eating" << logger::endl;

			int dineroEnCaja = caja.read();
			noCobrado = dineroPorCobrar.read();
			dineroPorCobrar.write(noCobrado - costoDePlato);
			caja.write(dineroEnCaja + costoDePlato);
		}
		catch (const OSException& ex){
			keepAlive = false;
		}
		LobbyMonitor::getInstance().increaseFreeTables();
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
