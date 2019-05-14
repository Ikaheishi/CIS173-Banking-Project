#include "actmanager.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>

ATM_STATUS
AccountManager::login(std::string username, std::string* pascode){
	try{
		activeHandle = usernameMap.at(username).front();
	}
	catch(std::out_of_range ex){
		return ATM_STATUS::ACT_INVALID;
	}
	if(activeHandle.login(pascode)){
		current = &activeHandle;
		return ATM_STATUS::SUCCESS;
	}
	else
		return ATM_STATUS::ACT_PASS;
}
ATM_STATUS
AccountManager::logout(void){
	current = nullptr;
	return ATM_STATUS::SUCCESS;
}

bool
AccountManager::usernameExists(std::string username){
	return usernameMap.count(username) > 0;
}

ATM_STATUS
AccountManager::createUser(std::string username, std::string* passcode){
	if(usernameExists(username))
		return ATM_STATUS::ACT_EXIST;

	std::list<Account> new_user = std::list<Account>();

	Account new_account = Account(++lastID, passcode);
	new_user.push_back(new_account);

	usernameMap[username] = new_user;
	accountMap[lastID] = new_account;

	return ATM_STATUS::SUCCESS;
}