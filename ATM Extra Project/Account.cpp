#include "utils.hpp"
#include "account.hpp"
#include "atmstatus.hpp"

Account::Account(uint64_t accountID, std::string* passcode) {
	id = accountID;
	pchash = utils::hashpw(passcode);
	balance = 0;
}
Account::Account(uint64_t accountID, uint64_t hash, double initialBalance) {
	id = accountID;
	pchash = hash;
	balance = initialBalance;
}
Account::Account() {
	id = 0; pchash = 0; balance = 0;
}
ATM_STATUS Account::withdraw(double amount) {
	if (hold) return ATM_STATUS::ACT_HOLD;
	if (balance >= amount) {
		balance -= amount;
		return ATM_STATUS::SUCCESS;
	}
	else return ATM_STATUS::FUNDS_INSUFFICENT;
}

ATM_STATUS Account::deposit(double amount) {
	if (hold) return ATM_STATUS::ACT_HOLD;
	if (amount > 0) {
		balance += amount;
		return ATM_STATUS::SUCCESS;
	}
	else return ATM_STATUS::UNK_ERROR;
}

double Account::checkBalance(void) {
	return balance;
}

bool Account::login(std::string* passcode) {
	return utils::hashpw(passcode) == pchash;
}