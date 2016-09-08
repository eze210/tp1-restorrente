#include "RandomSleep.h"

#include <unistd.h>
#include <cstdlib>
#include <iostream>
#include <stddef.h>
#include <sys/shm.h>


long int RandomSleep::random(){
	srand(getpid());
	return (rand() % 30);
}

int RandomSleep::start(int getId, int idx){
	this->getId = getId;
	this->idx = idx;
	MyProcess::start();
	return 0;
}

int RandomSleep::run() {
	int *array = (int*) shmat(getId, NULL, 0);
	int sleepTime = random();
	sleep(sleepTime);
	array[idx] = sleepTime;
	shmdt(array);
	return 0;
}

RandomSleep::~RandomSleep() {
}

