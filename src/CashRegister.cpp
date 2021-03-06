#include "CashRegister.h"
#include "LockedScope.h"

const static std::string cashRegisterMutexFileName("cash-reg.mutex");

CashRegister::CashRegister() :
				cash(__FILE__, 'c'),
				uncollected(__FILE__, 'u'),
				cashMutex(cashRegisterMutexFileName)
{
}

CashRegister &CashRegister::getInstance() {
	static CashRegister staticInstance;
	return staticInstance;
}

void CashRegister::addPayment(int amount) {
	LockedScope l(cashMutex);
	int uncollectedAmount = uncollected.read();
	int collectedAmount = cash.read();
	if ((uncollectedAmount - amount) < 0)
		return;

	uncollectedAmount -= amount;
	collectedAmount += amount;

	uncollected.write(uncollectedAmount);
	cash.write(collectedAmount);
}

void CashRegister::addPaymentPromise(int amount) {
	LockedScope l(cashMutex);

	int uncollectedAmount = uncollected.read();
	uncollectedAmount += amount;
	uncollected.write(uncollectedAmount);
}

int CashRegister::getUncollectedMoney() {
	//LockedScope l(cashMutex);
	return uncollected.read();
}

int CashRegister::getMoneyInCashRegister() {
	LockedScope l(cashMutex);
	return cash.read();
}

void CashRegister::clearUncollectedMoney() {
	LockedScope l(cashMutex);
	uncollected.write(0);
}

void CashRegister::init() {
	LockedScope l(cashMutex);
	cash.write(0);
	uncollected.write(0);
}

#include "OSException.h"
#include "Logger.h"

void CashRegister::release() {
	try {
	cashMutex.release();
	cash.free();
	uncollected.free();

	}
	catch(const OSException &e) {
		LOGGER << e.what() << logger::endl;
	}
}

CashRegister::~CashRegister() {
}
