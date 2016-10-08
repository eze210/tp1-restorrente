#ifndef FIFO_H_
#define FIFO_H_

#include <string>

class Fifo {
public:
    explicit Fifo(const std::string &fileName);

    virtual ~Fifo();

    virtual void open() = 0;

    void close();

    void release() const;

protected:
    const std::string fileName;
    int fileDescriptor;
};

#endif
