#include "FifoWrite.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>

FifoWrite::FifoWrite(const std::string &fileName) : Fifo(fileName) {
	open();
}

FifoWrite::~FifoWrite() {
}

void FifoWrite::open() {
	fileDescriptor = ::open(fileName.c_str(), O_WRONLY);
	if (fileDescriptor == invalidFileDescriptor)
		throw OSException();
}

ssize_t FifoWrite::write(const void *buffer, const ssize_t bufferSize) const {
	ssize_t result = ::write(fileDescriptor, buffer, bufferSize);
	if (result == -1)
		throw OSException();
	return result;
}
