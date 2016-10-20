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
#include <utils/SignalHandler.h>
#include <event_handlers/KillHandler.h>

#define CLIENTS_COUNT 2

const static std::string kitchenMutexName("Kitchen.cpp");
const static std::string cajaMem("caja.mem");
const static std::string noCobradoMem("no-cobrado.mem");
const static std::string cajaMutexName("caja.mutex");
const static std::string noCobradoMutexName("no-cobrado.mutex");

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


		SharedMemory<int> caja(cajaMem, 1);
		LOGGER << "LLEGAAAA" << logger::endl;
		Mutex cajaMutex(cajaMutexName);


		SharedMemory<int> dineroPorCobrar(noCobradoMem,2);
		Mutex noCobradoMutex(noCobradoMutexName);

		cajaMutex.lock();
		caja.write(0);
		cajaMutex.unlock();

		noCobradoMutex.lock();
		dineroPorCobrar.write(0);
		noCobradoMutex.unlock();

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

		KillHandler handler(caja, dineroPorCobrar);
		SignalHandler::getInstance().registerHandler(SIGINT, &handler);


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
		caja.free();
		dineroPorCobrar.free();
	}
	catch(const std::exception& e) {
		LOGGER << "Exception catched: " << e.what() << logger::endl;
	}

	return 0;
}
