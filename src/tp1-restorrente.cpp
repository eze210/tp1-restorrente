#include "ExampleProcess.h"
#include <iostream>

int main(int argc, char *argv[]) {
	ExampleProcess childProcess;
	std::cout << "The main process has started." << std::endl;
	childProcess.start();
	std::cout << "The main process is waiting its child." << std::endl;
	std::cout << "Child's exit value: " << childProcess.wait() << std::endl;
	return 0;
}
