#include <stddef.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <errno.h>
#include <vector>
#include <cinttypes>

#include "Logger.h"
#include "OSException.h"
#include "RandomSleep.h"
#include "SharedMemory.h"

/**
 * g++ -Wall -Werror -pedantic -std=c++0x *.cpp -ggdb -O3 -o ej
 */

int main(int argc, char *argv[]) {
	int idGet = -1;
	int *array = NULL;
	try {
		SharedMemory<int> integer("/bin/bash", 1);
		if (argc != 2) {
			std::cout << "usage: " << argv[0] << " numberOfChildren" << std::endl;
			return 1;
		}

		integer.write(4);

		std::stringstream ss;
		ss << argv[1];
		int numberOfChildren;
		ss >> numberOfChildren;
		std::vector<RandomSleep> children(numberOfChildren);

		key_t key = ftok("/bin/bash", 0);
		LOGGER << "Key: " << key << logger::endl;
		if (key == -1) {
			throw OSException();
		}
		idGet = shmget(key, numberOfChildren * sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
		LOGGER << "ID Get: " << idGet << logger::endl;
		if (idGet == -1) {
			throw OSException();
		}

		void *arrayV = shmat(idGet, 0, 0);
		LOGGER << "Attach: " << (int64_t)arrayV << logger::endl;
		if((int64_t)arrayV == -1) {
			throw OSException();
		}
		array = (int*)arrayV;

		for (int i = 0; i < numberOfChildren; ++i) {
			children[i].start(idGet, i);
		}
		for (int j = 0; j < numberOfChildren; ++j) {
			children[j].wait();
			std::cout << "Child slept " << array[j] << " seconds" << std::endl;
		}
	}
	catch(const std::exception &ex) {
		LOGGER << "Exception: " << ex.what() << logger::endl;
	}

	shmdt(array);
	shmctl(idGet, IPC_RMID, NULL);

	return 0;
}
