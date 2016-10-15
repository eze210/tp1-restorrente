#include "Config.h"
#include "Door.h"
#include "Receptionist.h"
#include "ClientsGenerator.h"
#include "Table.h"
#include <vector>

int main() {
	Config::loadConfig();
	std::cout <<
			"Recepcionistas: " << Config::getReceptionistsCount() <<
			"\nMozos: " << Config::getWaitersCount() <<
			"\nMesas: " << Config::getTablesCount() << std::endl;

	std::vector<Food> foods;
	foods = Config::getAvailableFoods();
	std::cout << "Comidas: " << foods.size() << std::endl;

	for (ssize_t i = 0; i < Config::getTablesCount(); ++i)
		LobbyMonitor::getInstance().increaseFreeTables();

	Door door;
	ClientsGenerator generator;
	std::vector<Receptionist> recepcionists(
			Config::getReceptionistsCount(),
			Receptionist(door));
	std::vector<Table> tables(
			Config::getTablesCount());

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

	return 0;
}
