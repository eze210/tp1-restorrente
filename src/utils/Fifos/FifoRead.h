#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"
#include "Mutex.h"
#include <string>

class FifoRead : public Fifo {
private:
    Mutex mutex;

    void open();

public:
    explicit FifoRead(const std::string &fileName);

    ~FifoRead();

    ssize_t read(void *buffer, const ssize_t bufferSize);
};

#endif
