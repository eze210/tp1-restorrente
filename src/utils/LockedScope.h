#ifndef UTILS_LOCKEDSCOPE_H_
#define UTILS_LOCKEDSCOPE_H_

#include "Mutex.h"

class LockedScope {
private:
	Mutex &mutex;
public:
	explicit LockedScope(Mutex &mutex) : mutex(mutex){
		mutex.lock();
	}
	~LockedScope() {
		mutex.unlock();
	}
};

#endif
