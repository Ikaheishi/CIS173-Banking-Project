#include "macros.h"
#include "precheck.h"

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdint>
#include <type_traits>

#include <chrono>
#include <thread>

//#include <termios.h>
//#include <unistd.h>

#include "Account.hpp"
#include "ActManager.hpp"

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
enum AppContext : size_t {
	APP_INIT	= 0b0,	//Application startup
	MAINMENU	= 0b10,	//The initial menu
	LOGINMEMU	= 0b11,	//User's logged in menu
	USERAUTH	= 0b100,	//User login prompt
	ACT_SIGNUP	= 0b101,	//User account creation prompt
	ACT_SUBFUND	= 0b1000,	//Withdraw from account screen
	ACT_ADDFUND	= 0b1001,	//Deposit to account screen
	LOAN_ACT	= 0b1,	//Loan application for existing users
	LOAN_NEW	= 0b1,	//Loan application for new users
	APP_TERM	= 0b1,	//Graceful shutdown process
} context;

// global variable (use this variable to store the user’s menu selection)
char menuInput;
AccountManager accounts;
ATM_STATUS sys_status;
std::vector<MENUSET> OPT_IMENU;
std::vector<MENUSET> OPT_UMENU;
struct termios *TERM_SETTINGS;

// the main function
int main(){
	context = APP_INIT;
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
	context = MAINMENU;
	start();
	if (context == APP_TERM) {
	std::cout
		<< "Thanks for stopping by!"
		<< std::endl;
	return 0;
	}
	else {
		std::cout << "";
		return -1 & context;
	}
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
		printError("ERROR " + static_cast<std::underlying_type<ATM_STATUS>::type>(sys_status), 5);
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
	else while(context == LOGINMEMU){
		printMainMenu();

	umenu_prompt:
		std::cout << "] ";
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

/*	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═
	Outputs a given character the specified number of times.
	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═

	Arguments:
	​• char character
		The character to be repeatedly output on the screen.

	• size_t cx
		The number of times to output the character.
	​
	─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​
*/
void printLoop(char16_t character, size_t cx){
	for(; cx != 0; cx--){
		std::cout << character;
	}
}
//TODO: Generics?
/*	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═
	Outputs a given string the specified number of times.
	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═

	Arguments:
	​• std::string text
		The string to be repeatedly output on the screen.

	• size_t cx
		The number of times to output the string.
	​
	─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​
*/
void printLoop(std::string text, size_t cx) {
	for (; cx != 0; cx--) {
		std::cout << text;
	}
}

/*	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═
	Displays an error message to the screen.
	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═

	Arguments:
	​• std::string errorMessage
		The error message to be output on the screen.
	​
	─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​
	
	Note: This subroutine clears the entire screen from the second row
	onward. It does not wait for an amount of time, meaning that the message
	may be invisible to the user if the screen is blanked or the error
	message output is overwritten. Nor does this subroutine leave the cursor
	in a guaranteed location.
	​
	If you want to display an error for a specific period of time, use
	printError(std::string message, int8_t duration);
*/
void printError(std::string errorMessage) {
	size_t offset = TERM_WIDTH / 2 - errorMessage.length() / 2;

	std::cout << MCR(2, 0) CLD MCR(6, 0) RED;
	//std::cout << errorMessage.find_last_of(' ', errorMessage.length()/2);

	std::cout << CSI << offset << "c╔"; //ex: "\e[5c" move forward by 5 cols
	printLoop('═', errorMessage.length() + 4);
	std::cout << "╗\n" << offset << "║";
	std::cout << "║ " << errorMessage << " ║\n╚";
	printLoop('═', errorMessage.length() + 4);
	std::cout << "╝\n\n";

	std::flush(std::cout);
}

/*	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═
	Displays an error message to the screen for the specified time in seconds
	​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═​═

	Arguments:
	​• std::string errorMessage
		The error message to be output on the screen.
	
	​• uint8_t duration
		The amount of time to display the error message on screen, before
		blanking and returning the terminal to a guarenteed state.
	​
	─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​─​
	
	Note: This subroutine clears the entire screen from the second row
	onward. The terminal cursor is guaranteed to be left at the beginning of
	the second row.
*/
void printError(std::string errorMessage, int8_t duration){
	printError(errorMessage);
	std::this_thread::sleep_for(std::chrono::seconds(duration));

	std::cout << RST MCR(2, 0) CLD;
}
