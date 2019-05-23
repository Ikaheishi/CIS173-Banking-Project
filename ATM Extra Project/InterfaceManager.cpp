#include "macros.h"

#include <iostream>
#include <string>

#include <chrono>
#include <thread>

#include "InterfaceManager.hpp"

#define inStream std::cin
#define outStream std::cout

InterfaceManager::InterfaceManager()
{
	
}
InterfaceManager::~InterfaceManager()
{

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
void InterfaceManager::printLoop(char16_t character, size_t cx) {
	for (; cx != 0; cx--) {
		outStream << character;
	}
}
//TODO: Reimplement `printLoop()` via the concept of generics?
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
void InterfaceManager::printLoop(std::string text, size_t cx) {
	for (; cx != 0; cx--) {
		outStream << text;
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
void InterfaceManager::printError(std::string errorMessage) {
	size_t offset = TERM_WIDTH / 2 - errorMessage.length() / 2;

	outStream << ANSI_CUP(2, 0) ANSI_ED(0) ANSI_CUP(6, 0) ANSI_SGR(31);
	//outStream << errorMessage.find_last_of(' ', errorMessage.length()/2);

	outStream << ANSI_CSI << offset << ANSI_CSFB_CHA CHR_BORDER_CORNER_TL; //ex: "\e[5C" move forward by 5 cols
	printLoop(CHR_BORDER_TOP, errorMessage.length() + 2);
	outStream << CHR_BORDER_CORNER_TR "\n" ANSI_CSI << offset << ANSI_CSFB_CHA;

	outStream << CHR_BORDER_LEFT " " << errorMessage << " " CHR_BORDER_RIGHT "\n";

	outStream << ANSI_CSI << offset << ANSI_CSFB_CHA CHR_BORDER_CORNER_BL;
	printLoop(CHR_BORDER_BOTTOM, errorMessage.length() + 2);
	outStream << CHR_BORDER_CORNER_BR "\n\n" ANSI_SGR(0);

	std::flush(outStream);
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
void InterfaceManager::printError(std::string errorMessage, int8_t duration) {
	printError(errorMessage);
	std::this_thread::sleep_for(std::chrono::seconds(duration));

	outStream << ANSI_SGR(0) ANSI_CUP(2, 0) ANSI_ED(0);
}
