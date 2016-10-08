#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"
#include <string>

class FifoWrite : public Fifo {
private:
    void open();

public:
    explicit FifoWrite(const std::string &fileName);

    ~FifoWrite();

    ssize_t write(const void *buffer, const ssize_t bufferSize) const;
};

#endif
