#include "Fifo.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include "LockedScope.h"
#include <iostream>

const int Fifo::invalidFileDescriptor = -1;

Fifo::Fifo(const std::string &fileName) :
        		fileName(fileName),
				fileDescriptor(invalidFileDescriptor) {
	::mknod(static_cast<const char *>(fileName.c_str()), S_IFIFO | 0666, 0);
}

Fifo::~Fifo() {
	close();
}

void Fifo::close() {
	if (fileDescriptor != invalidFileDescriptor) {
		::close(fileDescriptor);
		fileDescriptor = invalidFileDescriptor;
	}
}

void Fifo::release() {
	close();
	::unlink(fileName.c_str());
}
