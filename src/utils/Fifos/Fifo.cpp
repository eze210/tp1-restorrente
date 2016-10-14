#include "Fifo.h"
#include <sys/stat.h>
#include <unistd.h>
#include <string>

const int Fifo::invalidFileDescriptor = -1;

Fifo::Fifo(const std::string &fileName) :
        fileName(fileName), fileDescriptor(invalidFileDescriptor) {
    ::mknod(static_cast<const char *>(fileName.c_str()), S_IFIFO | 0666, 0);
}

Fifo::~Fifo() {
	if (fileDescriptor != invalidFileDescriptor)
		close();
}

void Fifo::close() {
    ::close(fileDescriptor);
    fileDescriptor = invalidFileDescriptor;
}

void Fifo::release() const {
    ::unlink(fileName.c_str());
}
