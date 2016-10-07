#ifndef CLIENTSGROUP_H_
#define CLIENTSGROUP_H_

#include <unistd.h>

class ClientsGroup {
private:
	int id;
public:
	explicit ClientsGroup(int id) : id(id) {
	}
	void eat() {
		sleep(1);
	}
};

#endif
