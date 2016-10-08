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
}

ssize_t FifoWrite::write(const void *buffer, const ssize_t bufferSize) const {
    return ::write(fileDescriptor, buffer, bufferSize);
}
