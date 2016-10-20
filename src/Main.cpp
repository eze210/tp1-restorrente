#include "Config.h"
#include "Door.h"
#include "Receptionist.h"
#include "ClientsGenerator.h"
#include "Table.h"
#include "Kitchen.h"
#include <vector>
#include <utils/Semaphore.h>
#include <processes/Waiter.h>
#include <utils/Logger.h>

#define CLIENTS_COUNT 2

const static std::string kitchenMutexName("Kitchen.cpp");

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

		for (ssize_t i = 0; i < Config::getTablesCount(); ++i)
			LobbyMonitor::getInstance().increaseFreeTables();

		Door door;
		ClientsGenerator generator(CLIENTS_COUNT);
		generator.start();
		std::vector<Receptionist> recepcionists(
				Config::getReceptionistsCount(),
				Receptionist(door));

		WaitersQueue waitersQueue;
		LockFile lockFile(kitchenMutexName);
		Kitchen kitchen(lockFile);
		std::vector<Table> tables(
				Config::getTablesCount(), Table(waitersQueue, kitchen));


		/* forks all processes */
		for (Receptionist &recepcionist : recepcionists) {
			recepcionist.start();
		}

		for (Table &table : tables) {
			table.start();
		}

		/* waits children */
		generator.wait();
		for (Receptionist &recepcionist : recepcionists) {
			recepcionist.wait();
		}
		for (Table &table : tables) {
			table.wait();
		}


		door.releaseFifo();
		LobbyMonitor::getInstance().release();
	}
	catch(const std::exception& e) {
		LOGGER << "Exception catched: " << e.what() << logger::endl;
	}

	return 0;
}
