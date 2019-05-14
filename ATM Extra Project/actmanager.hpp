#pragma once
#include <string>
#include <functional>
#include <list>
#include <unordered_map>
#include <cstdint>
#include "account.hpp"
#include "atmstatus.hpp"
class AccountManager {
public:
	Account *current;
	ATM_STATUS login(std::string username, std::string *pascode);
	ATM_STATUS logout(void);
	bool usernameExists(std::string username);
	ATM_STATUS createUser(std::string username, std::string* passcode);
	//Account* getAccount(std::string login);
	//Account* getAccount(uint64_t account_number);
private:
	Account defaultAccount = Account(0, 0, 0.0);
	Account activeHandle = defaultAccount;
	uint64_t lastID = 0;
	std::unordered_map<std::string, std::list<Account>> usernameMap;
	std::unordered_map<uint64_t, Account> accountMap;
};
