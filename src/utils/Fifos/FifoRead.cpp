#include "FifoRead.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include <iostream>

FifoRead::FifoRead(const std::string &fileName) : Fifo(fileName) {
    open();
}

FifoRead::~FifoRead() {
}

void FifoRead::open() {
    fileDescriptor = ::open(fileName.c_str(), O_RDONLY);
    if (fileDescriptor == invalidFileDescriptor)
    	throw OSException();
}

ssize_t FifoRead::read(void *buffer, const ssize_t bufferSize) const {
	std::cout << "reading from " << this->fileName << std::endl;
    ssize_t result = ::read(fileDescriptor, buffer, bufferSize);
    std::cout << "readed " << result << " bytes from " << this->fileName << std::endl;
    if (result == -1)
    	throw OSException();
    return result;
}
