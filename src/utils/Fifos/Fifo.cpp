#include "Fifo.h"
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#define INVALID_FILE_DESCRIPTOR (-1)

Fifo::Fifo(const std::string &fileName) :
		fileName(fileName), fileDescriptor(INVALID_FILE_DESCRIPTOR) {
	::mknod(static_cast<const char*>(fileName.c_str()), S_IFIFO|0666, 0);
}

Fifo::~Fifo() {
}

void Fifo::close() {
	::close(fileDescriptor);
	fileDescriptor = INVALID_FILE_DESCRIPTOR;
}

void Fifo::release() const {
	::unlink(fileName.c_str());
}
