#include "Config.h"
#include "Door.h"
#include "Receptionist.h"
#include "ClientsGenerator.h"
#include "Table.h"
#include "Kitchen.h"
#include <vector>
#include <utils/Semaphore.h>
#include <processes/Waiter.h>

#define CLIENTS_COUNT 10


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
	Config::loadConfig();
	printConf();

	for (ssize_t i = 0; i < Config::getTablesCount(); ++i)
		LobbyMonitor::getInstance().increaseFreeTables();

	Door door;
	ClientsGenerator generator(CLIENTS_COUNT);
	std::vector<Receptionist> recepcionists(
			Config::getReceptionistsCount(),
			Receptionist(door));

	WaitersQueue waitersQueue;
	std::vector<Table> tables(
			Config::getTablesCount(), Table(waitersQueue));

	Kitchen kitchen;
	kitchen.start();

	/* forks all processes */
	for (Receptionist &recepcionist : recepcionists) {
		recepcionist.start();
	}

	generator.start();
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
	kitchen.wait();


	return 0;
}
