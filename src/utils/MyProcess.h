#ifndef MYPROCESS_H_
#define MYPROCESS_H_

#include <unistd.h>

class MyProcess {
private:
    pid_t pid;
public:
    void start();
    int wait();
    virtual int run() = 0;
    virtual ~MyProcess();
};

#endif
