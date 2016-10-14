#ifndef FIFO_H_
#define FIFO_H_

#include <string>
#include "OSException.h"

class Fifo {
public:
    explicit Fifo(const std::string &fileName);
    virtual ~Fifo();
    virtual void open() = 0;
    void close();
    void release() const;
    static const int invalidFileDescriptor;

protected:
    const std::string fileName;
    int fileDescriptor;
};

#endif
