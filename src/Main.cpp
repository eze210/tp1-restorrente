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
	std::cout << "Comidas:" << std::endl;
	for (size_t i = 0; i < foods.size(); i++) {
		std::cout << foods.at(i).serialize() << ";";
	}

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

	return 0;
}
