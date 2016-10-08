#ifndef SHAREDMEMORY_H_
#define SHAREDMEMORY_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <cerrno>
#include "OSException.h"

template<class T>
class SharedMemory {
private:
    int sharedMemoryID;
    T *dataPointer;
    int numberOfAttachedProcesses() const;

public:
    SharedMemory();
    void create(const std::string &fileName, const char character);
    void free();
    SharedMemory(const std::string &fileName, const char character);
    SharedMemory(const SharedMemory &another);
    ~SharedMemory();
    SharedMemory<T> &operator=(const SharedMemory &another);
    void write(const T &data);
    T read() const;
};

template<class T>
SharedMemory<T>::SharedMemory() :
        sharedMemoryID(0),
        dataPointer(NULL) {
}

template<class T>
void SharedMemory<T>::create(
        const std::string &fileName,
        const char character) {
    key_t key = ftok(fileName.c_str(), character);
    if (key <= 0)
        throw OSException();

    this->sharedMemoryID = shmget(key, sizeof(T), 0644 | IPC_CREAT);
    if (this->sharedMemoryID <= 0)
        throw OSException();

    void *tmpPtr = shmat(this->sharedMemoryID, NULL, 0);
    if (tmpPtr == (void *) -1)
        throw OSException();

    this->dataPointer = static_cast<T *> (tmpPtr);
}

template<class T>
void SharedMemory<T>::free() {
    int errorDt = shmdt((void *) this->dataPointer);
    if (errorDt == -1)
        throw OSException();

    if (this->numberOfAttachedProcesses() == 0)
        shmctl(this->sharedMemoryID, IPC_RMID, NULL);
}

template<class T>
SharedMemory<T>::SharedMemory(
        const std::string &fileName,
        const char character) :
        sharedMemoryID(0), dataPointer(NULL) {
    this->create(fileName, character);
}

template<class T>
SharedMemory<T>::SharedMemory(const SharedMemory &another) :
        sharedMemoryID(another.sharedMemoryID) {
    void *tmpPtr = shmat(another.sharedMemoryID, NULL, 0);
    if (tmpPtr == (void *) -1)
        throw OSException();

    this->dataPointer = static_cast<T *> (tmpPtr);
}

template<class T>
SharedMemory<T>::~SharedMemory() {
    this->free();
}

template<class T>
SharedMemory<T> &SharedMemory<T>::operator=(
        const SharedMemory &another) {
    this->sharedMemoryID = another.sharedMemoryID;
    void *tmpPtr = shmat(this->sharedMemoryID, NULL, 0);

    if (tmpPtr == (void *) -1)
        throw OSException();

    this->dataPointer = static_cast<T *> (tmpPtr);
    return *this;
}

template<class T>
void SharedMemory<T>::write(const T &data) {
    *(this->dataPointer) = data;
}

template<class T>
T SharedMemory<T>::read() const {
    return *(this->dataPointer);
}

template<class T>
int SharedMemory<T>::numberOfAttachedProcesses() const {
    shmid_ds status;
    shmctl(this->sharedMemoryID, IPC_STAT, &status);
    return status.shm_nattch;
}

#endif
