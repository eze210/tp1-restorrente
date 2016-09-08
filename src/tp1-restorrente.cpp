#include <iostream>

#include "ExampleProcess.h"
#include "Logger.h"
#include "OSException.h"

int main(int argc, char *argv[]) {
	try {
		ExampleProcess childProcess;
		std::cout << "The main process has started." << std::endl;
		childProcess.start();
		std::cout << "The main process is waiting its child." << std::endl;
		std::cout << "Child's exit value: " << childProcess.wait() << std::endl;
		throw OSException();
	}
	catch(const std::exception& e) {
		LOGGER << "Received exception: " << e.what() << logger::endl;
	}

	return 0;
}
