#include "../includes/Utils.hpp"

bool isOnlyDigitString(std::string str)
{
	for (char c : str)
	{
		if (isdigit(c) == false)
			return false;
	}
	return true;
}

bool isValidPassword(std::string str)
{
	if (str.length() < 8 || str.length() > 20)
		return false;
	for (char c : str)
	{
		if (!strchr(VALID_CHARACTERS, c) && !isalnum(c))
			return false;
	}
	return true;
}

std::string firstWord(std::string commandLine) {
	std::istringstream iss(commandLine);
	std::string firstWord;
	iss >> firstWord;
	return firstWord;
}
