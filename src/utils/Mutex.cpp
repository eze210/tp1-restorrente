#include "Mutex.h"
#include "OSException.h"
#include <unistd.h>
#include <string>
#include <iostream>

#define SYSTEM_ERROR (-1)

Mutex::Mutex(const std::string &fileName) :
        fileDescriptor(open(fileName.c_str(), O_CREAT | O_WRONLY, 0777)),
		fileName(fileName) {
    if (fileDescriptor == SYSTEM_ERROR)
        throw OSException();

    flock.l_type = F_WRLCK;
    flock.l_whence = SEEK_SET;
    flock.l_start = 0;
    flock.l_len = 0;
}

void Mutex::lock() {
	std::cout << "locking a lock for write: " << this->fileName << std::endl;
	flock.l_type = F_WRLCK;
    if (fcntl(fileDescriptor, F_SETLKW, &flock) == SYSTEM_ERROR)
        throw OSException();
}

void Mutex::unlock() {
	std::cout << "unlocking a lock for write: " << this->fileName << std::endl;
	flock.l_type = F_UNLCK;
    if (fcntl(fileDescriptor, F_SETLK, &flock) == SYSTEM_ERROR)
        throw OSException();
}

Mutex::~Mutex() {
    if (close(fileDescriptor) == SYSTEM_ERROR)
        throw OSException();
}
