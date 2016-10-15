#include "Table.h"
#include "LobbyMonitor.h"
#include "Logger.h"

Table::Table() : keepAlive(true) {
}

int Table::run() {
	while (keepAlive) {
		try {
			ClientsGroup clients = LobbyMonitor::getInstance().getClients();
			LOGGER << "The clients " << clients.getID() <<
					" are in their table" << logger::endl;
			clients.eat();
		}
		catch (const OSException& ex){
			keepAlive = false;
		}
	}
	return 0;
}

Table::~Table() {
}
