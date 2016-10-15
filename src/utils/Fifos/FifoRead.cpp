#include "FifoRead.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>

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
    ssize_t result = ::read(fileDescriptor, buffer, bufferSize);
    if (result != bufferSize)
    	throw OSException();
    return result;
}
