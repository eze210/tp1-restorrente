#include "Config.h"
#include "Door.h"
#include "Receptionist.h"
#include "ClientsGenerator.h"
#include "Table.h"
#include "Kitchen.h"

#include "Waiter.h"
#include "Logger.h"
#include "SignalHandler.h"
#include "KillHandler.h"
#include "ProcesesKillHandler.h"
#include "Manager.h"
#include "CashRegister.h"

#include <vector>

#define CLIENTS_COUNT 2
#define SIGNAL_KILL 2

void printConf() {
	std::cout <<
			"Recepcionistas: " << Config::getReceptionistsCount() <<
			"\nMozos: " << Config::getWaitersCount() <<
			"\nMesas: " << Config::getTablesCount() << std::endl;

	std::vector<Food> foods;
	foods = Config::getAvailableFoods();
	std::cout << "Comidas: " << foods.size() << std::endl;
}


int main(int argc, char** argv) {
	try {
		Config::loadConfig();
		printConf();

		Door door;
		ClientsGenerator generator(CLIENTS_COUNT);
		generator.start();

		std::vector<Receptionist> recepcionists(
				Config::getReceptionistsCount(),
				Receptionist(door));

		WaitersQueue waitersQueue;
		Kitchen kitchen;
		std::vector<Table> tables(
				Config::getTablesCount(),
				Table(waitersQueue, kitchen));

		ProcesesKillHandler procesesKillHandler;
		SignalHandler::getInstance().registerHandler(
				SIGINT,
				&procesesKillHandler);

		CashRegister::getInstance().init();

		Manager manager;
		manager.start();

		/* forks all processes */
		for (Receptionist &recepcionist : recepcionists) {
			recepcionist.start();
		}

		for (Table &table : tables) {
			table.start();
		}

		KillHandler handler;
		SignalHandler::getInstance().registerHandler(SIGINT, &handler);

		/* waits children */
		generator.wait();
		for (Receptionist &recepcionist : recepcionists) {
			recepcionist.wait();
			LOGGER << "RECEPCIONISTA LIBERADO" << logger::endl;
		}

		for (Table &table : tables) {
			LOGGER << "LIBERANDO MESA" << logger::endl;
			table.wait();
		}

		LOGGER << "LIBERANDO MANAGER" << logger::endl;
		manager.wait();

		LOGGER << "LIBERANDO DOOR" << logger::endl;
		door.releaseFifo();

		LOGGER << "LIBERANDO LOBBY MONITOR" << logger::endl;
		LobbyMonitor::getInstance().release();

		CashRegister::getInstance().release();

		LOGGER << "EL RESTORRENTE TERMINO CORRECTAMENTE" << logger::endl;
		return 0;
	}
	catch(const std::exception& e) {
		LOGGER << "Exception catched: " << e.what() << logger::endl;
	}
	catch(int returnCode) {
		return returnCode;
	}

	return 0;
}
