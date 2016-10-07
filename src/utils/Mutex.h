#ifndef UTILS_MUTEX_H_
#define UTILS_MUTEX_H_

#include <fcntl.h>
#include <string>

class Mutex {
private:
	struct flock flock;
	int fileDescriptor;

public:
	explicit Mutex(const std::string &fileName);
	void lock();
	void unlock();
	~Mutex();
};

#endif
