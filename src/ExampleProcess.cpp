#include "ExampleProcess.h"
#include <iostream>

int ExampleProcess::run() {
	std::cout << "This is an example process." << std::endl;
	return 0;
}


ExampleProcess::~ExampleProcess() {
}

