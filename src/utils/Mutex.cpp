#include "Mutex.h"
#include "OSException.h"
#include <unistd.h>
#include <string>
#include <iostream>

#define SYSTEM_ERROR (-1)
const int Mutex::invalidFileDescriptor = -1;

Mutex::Mutex(const std::string &fileName) :
        fileDescriptor(open(fileName.c_str(), O_CREAT | O_WRONLY, 0777)),
		fileName(fileName) {
    if (fileDescriptor == invalidFileDescriptor)
        throw OSException();

    flock.l_type = F_WRLCK;
    flock.l_whence = SEEK_SET;
    flock.l_start = 0;
    flock.l_len = 0;
}

void Mutex::lock() {
	flock.l_type = F_WRLCK;
    if (fcntl(fileDescriptor, F_SETLKW, &flock) == SYSTEM_ERROR)
        throw OSException();
}

void Mutex::unlock() {
	flock.l_type = F_UNLCK;
    if (fcntl(fileDescriptor, F_SETLK, &flock) == SYSTEM_ERROR)
        throw OSException();
}

void Mutex::release() {
	if (fileDescriptor != invalidFileDescriptor)
		close(fileDescriptor);

	unlink(fileName.c_str());

	fileDescriptor = invalidFileDescriptor;
}

Mutex::~Mutex() {
	if (fileDescriptor == invalidFileDescriptor)
		return;

	if (close(fileDescriptor) == SYSTEM_ERROR)
        throw OSException();

	fileDescriptor = invalidFileDescriptor;
}
