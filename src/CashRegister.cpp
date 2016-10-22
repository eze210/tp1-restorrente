#include "CashRegister.h"
#include "LockedScope.h"

const static std::string cashRegisterMem("cash-reg.mem");
const static std::string uncollectedMem("cash-reg-uncollected.mem");
const static std::string cashRegisterMutexFileName("cash-reg.mutex");

CashRegister::CashRegister() :
				cash(cashRegisterMem, 'c'),
				uncollected(uncollectedMem, 'u'),
				cashMutex(cashRegisterMutexFileName)
{
}

CashRegister &CashRegister::getInstance() {
	static CashRegister staticInstance;
	return staticInstance;
}

void CashRegister::addPayment(unsigned int amount) {
	LockedScope l(cashMutex);
	unsigned int uncollectedAmount = uncollected.read();
	unsigned int collectedAmount = cash.read();

	uncollectedAmount -= amount;
	collectedAmount += amount;

	uncollected.write(uncollectedAmount);
	cash.write(collectedAmount);
}

void CashRegister::addPaymentPromise(unsigned int amount) {
	LockedScope l(cashMutex);

	unsigned int uncollectedAmount = uncollected.read();
	uncollectedAmount += amount;
	uncollected.write(uncollectedAmount);
}

unsigned int CashRegister::getUncollectedMoney() {
	LockedScope l(cashMutex);
	return uncollected.read();
}

unsigned int CashRegister::getMoneyInCashRegister() {
	LockedScope l(cashMutex);
	return cash.read();
}

CashRegister::~CashRegister() {
}
