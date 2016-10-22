#include "FifoRead.h"
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include "LockedScope.h"

FifoRead::FifoRead(const std::string &fileName) :
Fifo(fileName), mutex(fileName + ".mutex") {
    open();
}

FifoRead::~FifoRead() {
}

void FifoRead::open() {
    fileDescriptor = ::open(fileName.c_str(), O_RDONLY);
    if (fileDescriptor == invalidFileDescriptor)
    	throw OSException();
}

ssize_t FifoRead::read(void *buffer, const ssize_t bufferSize) {
	LockedScope l(mutex);

	ssize_t readed = 0;
	while (readed < bufferSize) {
		ssize_t result = ::read(fileDescriptor, buffer, bufferSize);
		if (result <= 0)
			throw OSException();
		readed += result;
	}

    return readed;
}
