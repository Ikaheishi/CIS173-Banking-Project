#pragma once
#include <string>
#include <cstdint>
#include "atmstatus.hpp"

class Account{
public:
	Account(std::uint64_t account_number, std::uint64_t passcode_hash, double balance);
	Account(std::uint64_t account_number, std::string* passcode);
	Account();
	ATM_STATUS withdraw(double ammount);
	ATM_STATUS deposit(double ammount);
	double checkBalance(void);
	bool login(std::string* pascode);
private:
	std::uint64_t id;

	std::uint64_t pchash;

	double balance;
	bool hold;
};
