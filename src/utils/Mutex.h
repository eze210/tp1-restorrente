#ifndef UTILS_MUTEX_H_
#define UTILS_MUTEX_H_

#include <fcntl.h>
#include <string>

class Mutex {
private:
    struct flock flock;
    int fileDescriptor;
    const std::string fileName;

public:
    explicit Mutex(const std::string &fileName);
    void lock();
    void unlock();
    void release();
    ~Mutex();

    static const int invalidFileDescriptor;
};

#endif
