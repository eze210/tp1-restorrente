#include "FifoWrite.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>

FifoWrite::FifoWrite(const std::string &fileName) : Fifo(fileName) {
	open();
}

FifoWrite::~FifoWrite() {
}

void FifoWrite::open() {
	std::cout << "opening fifo: " << this->fileName << std::endl;
	fileDescriptor = ::open(fileName.c_str(), O_WRONLY);
	if (fileDescriptor == invalidFileDescriptor)
		throw OSException();
}

ssize_t FifoWrite::write(const void *buffer, const ssize_t bufferSize) const {
	std::cout << "writing to " << this->fileName << std::endl;
	ssize_t result = ::write(fileDescriptor, buffer, bufferSize);
	std::cout << "writed " << result << " bytes to " <<
			this->fileName << std::endl;
	if (result == -1)
		throw OSException();
	return result;
}
