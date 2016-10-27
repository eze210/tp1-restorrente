#ifndef CASHREGISTER_H_
#define CASHREGISTER_H_

#include "SharedMemory.h"
#include "Mutex.h"

class CashRegister {
private:
    SharedMemory<int> cash;
    SharedMemory<int> uncollected;
    Mutex cashMutex;
	CashRegister();

public:
	static CashRegister &getInstance();

	void addPayment(int amount);
	void addPaymentPromise(int amount);

	int getUncollectedMoney();
	int getMoneyInCashRegister();

	void init();
	void release();
	void clearUncollectedMoney();

	~CashRegister();
};

#endif
