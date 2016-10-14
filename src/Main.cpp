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
	Receptionist receptionist(door);
	Table table;

	receptionist.start();
	generator.start();
	table.start();

	generator.wait();
	table.wait();
	receptionist.wait();

	return 0;
}
