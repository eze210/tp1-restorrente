#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"
#include <string>

class FifoRead : public Fifo {
private:
    void open();

public:
    explicit FifoRead(const std::string &fileName);
    ssize_t read(void *buffer, const ssize_t bufferSize);
    ssize_t forceRead(void *buffer, const ssize_t bufferSize);
    ~FifoRead();
};

#endif
