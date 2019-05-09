#include "macros.h"
#include "precheck.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdint>

#include <chrono>
#include <thread>

//#include <termios.h>
//#include <unistd.h>

#include "account.hpp"
#include "actmanager.hpp"

// function prototypes
void printIntroMenu();
void printMainMenu();
void start();
void login();
void createAccount();
void loanApplication();
void printError(std::string errorMessage, int8_t duration);

// class/structure definitions
typedef struct MENUSET{
	MENUSET(const char sel, const std::string desc) : sel(sel), desc(desc){}
	char sel;
	std::string desc;
} MENUSET;

// global variable (use this variable to store the user’s menu selection)
char menuInput;
AccountManager accounts;
ATM_STATUS sys_status;
std::vector<MENUSET> OPT_IMENU;
std::vector<MENUSET> OPT_UMENU;
struct termios *TERM_SETTINGS;

// the main function
int main(){
	// Initialise our account access manager

	// Setup our menu options
	OPT_IMENU.push_back(MENUSET('L', "Login"));
	OPT_IMENU.push_back(MENUSET('C', "Create New Account"));
	OPT_IMENU.push_back(MENUSET('A', "Apply for A Loan"));
	OPT_IMENU.push_back(MENUSET('Q', "Quit"));

	OPT_UMENU.push_back(MENUSET('D', "Deposit Money"));
	OPT_UMENU.push_back(MENUSET('W', "Withdraw Money"));
	OPT_UMENU.push_back(MENUSET('R', "Request Balance"));
	OPT_UMENU.push_back(MENUSET(' ', ""));
	OPT_UMENU.push_back(MENUSET('A', "Apply for A Loan"));

	// TO WRITE A WELCOME MESSAGE HERE
	std::cout
		<< MCR(1, 1) CLD REV "Welcome to Eroh Family Bank ATM Machine!" RST
		<< std::endl;

	// call the function start
	start();
	std::cout
		<< "Thanks for stopping by!"
		<< std::endl;
	return 0;
}

void printIntroMenu(){
	for(unsigned short n = 0; n < OPT_IMENU.size(); n++){
		std::cout
			<< CSI "7;1m" // Bold & Inverse
			<< OPT_IMENU.at(n).sel
			<< RST " -> "
			<< OPT_IMENU.at(n).desc
			<< std::endl;
	}
	std::cout << std::endl;
}

void printMainMenu(){
	for(unsigned short n = 0; n < OPT_UMENU.size(); n++){
		std::cout
			<< CSI "7;1m" // Bold & Inverse
			<< OPT_UMENU.at(n).sel
			<< RST " -> "
			<< OPT_UMENU.at(n).desc
			<< std::endl;
	}
	std::cout << std::endl;
}

void start(){
	// EXPLANATION OF CODE THAT GOES HERE IS BELOW
	bool run = true;
	while(run){
		std::cout
			<< std::endl
			<< BLD "Please select an option from the menu below:" RST << std::endl
			<< std::endl;

		printIntroMenu();

	imenu_prompt:
		std::cout << "> ";

		//tcgetattr(0, TERM_SETTINGS);

		std::cin >> menuInput;

		switch(menuInput & 0b11011111){
		case 'Q':
			run = false;
			break;
		case 'L':
			login();
			break;

		case 'C':
			createAccount();
			break;

		case 'A':
			loanApplication();
			break;
			#include "./includes/debug_opts.cpp"
		default:
			std::cout << CSI "1F" CLN;
			goto imenu_prompt;
			// Break, while skipping menu output (it's still visible)
		}
	}
}

void createAccount(){
	std::string accountID, passcode;
	sys_status = ATM_STATUS::UNK_ERROR;

	do{
		std::cout
			<< MCR(3, 1) CLD "Please choose your user ID:"
			<< std::endl
			<< std::endl
			<< "> ";
		std::cin >> accountID;
		if(accounts.usernameExists(accountID)){
			std::cout
				<< std::endl
				<< std::endl
				<< REV "Please select a different user ID" RST
				<< MCR(5, 1) CLN;
			continue;
		}
		else{
			break;
		}
	} while(sys_status != ATM_STATUS::SUCCESS);
	std::cout
		<< "Please choose your password:"
		<< std::endl
		<< std::endl
		<< "> ";
	std::cin >> passcode;
	sys_status = accounts.createUser(accountID, &passcode);
	if(sys_status != ATM_STATUS::SUCCESS){
		printError("ERROR", 5);
	}
}

void login(){
	std::string accountID, passcode;
	sys_status = ATM_STATUS::SUCCESS;

	std::cout
		<< MCR(3, 1) CLD "Please enter your user ID:"
		<< std::endl
		<< std::endl
		<< "> ";
	std::cin >> accountID;

	std::cout
		<< std::endl
		<< "Please enter your password:"
		<< std::endl
		<< std::endl
		<< "> ";
	std::cin >> passcode;

	sys_status = accounts.login(accountID, &passcode);

	if(sys_status != ATM_STATUS::SUCCESS){
		// Login unsuccessful
		// Let's find out why and inform the user *appropriately*
		switch(sys_status){
		case ATM_STATUS::ACT_INVALID:
		case ATM_STATUS::ACT_PASS:
			printError("ACCOUNT AND PASSWORD DO NOT MATCH", 5);
			break;
		default:
			printError("UNKNOWN SYSTEM ERROR", 5);
		}
	}
	else{
		printMainMenu();

	umenu_prompt:
		std::cin >> menuInput;

		switch(menuInput){
		case 'W':
		case 'D':
		case 'Q':

		default:
			std::cout << CSI "1F" CLN;
			goto umenu_prompt;
			// Break, while skipping menu output (it's still visible)
		}
	}
}
void loanApplication(){

}
void printLoop(char character, size_t cx){
	for(; cx != 0; cx--){
		std::cout << character;
	}
}
void printError(std::string errorMessage, int8_t duration){
	size_t offset = TERM_WIDTH / 2 - errorMessage.length() / 2;

	std::cout << MCR(2, 0) CLD MCR(6, 0) RED;
	//std::cout << errorMessage.find_last_of(' ', errorMessage.length()/2);

	printLoop(' ', offset);
	printLoop('*', errorMessage.length() + 4);
	std::cout << "\n";
	printLoop(' ', offset);
	std::cout << "* " << errorMessage << " *\n";
	printLoop(' ', offset);
	printLoop('*', errorMessage.length() + 4);

	std::flush(std::cout);

	std::this_thread::sleep_for(std::chrono::seconds(duration));

	std::cout << RST MCR(2, 0) CLD;
}