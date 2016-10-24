#ifndef CASHREGISTER_H_
#define CASHREGISTER_H_

#include "SharedMemory.h"
#include "Mutex.h"

class CashRegister {
private:
    SharedMemory<unsigned int> cash;
    SharedMemory<unsigned int> uncollected;
    Mutex cashMutex;
	CashRegister();

public:
	static CashRegister &getInstance();

	void addPayment(unsigned int amount);
	void addPaymentPromise(unsigned int amount);

	unsigned int getUncollectedMoney();
	unsigned int getMoneyInCashRegister();

	void init();
	void release();
	void clearUncollectedMoney();

	~CashRegister();
};

#endif
