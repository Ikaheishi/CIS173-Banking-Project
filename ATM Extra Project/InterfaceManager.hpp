#pragma once
#include <iostream>
class InterfaceManager
{
public:
	InterfaceManager();
	~InterfaceManager();

	void printLoop(char16_t character, size_t cx);
	void printLoop(std::string text, size_t cx);

	void printError(std::string errorMessage);
	void printError(std::string errorMessage, int8_t duration);

private:
//	std::istream &inStream;
//	std::ostream &outStream;
};