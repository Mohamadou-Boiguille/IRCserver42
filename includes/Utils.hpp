#ifndef UTILS_HPP
#define UTILS_HPP

#define VALID_CHARACTERS  "~`!@#$%^&*()_-+={[}]|:;\"'<,>.?/"
#define ERR_BADPORT "port is not valid.\nUsage: port must be between 6660 and 6669"
#define ERR_BADPASSWORD "password is not valid.\nUsage: password must contain at least 8 characters and be less than 20 characters.\nIt can contain letters, digits and special characters :(~`!@#$%^&*()_-+={[}]|:;\"'<,>.?/)"
#define HOST "ft_irc"

#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <arpa/inet.h>
#include <map>
#include <vector>
#include <sys/epoll.h>
#include <cerrno>
#include <sstream>
#include <cctype>
#include <iostream>
#include <cctype>
#include <stdexcept>
#include <string>

bool isOnlyDigitString(std::string str);
bool isValidPassword(std::string str);
std::string firstWord(std::string commandLine);

#endif // !UTILS_HPP
