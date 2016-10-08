#ifndef TABLE_H_
#define TABLE_H_

#include "MyProcess.h"

class Table : public MyProcess {
private:
    bool keepAlive;
public:
    Table();

    int run();

    ~Table();
};

#endif
