#include "../includes/Server.hpp"
#include <memory>

int main (int argc, char *argv[]) {
	std::string port = "";
	std::string password = "";
	if (argc > 3 || argc < 2)
	{
		std::cerr << "Error: Usage: ft_irc <port> <password>" << std::endl;
		return 1;
	}
	if (argc >= 2)
		port = argv[1];
	if (argc == 3)
		password = argv[2];
	try
	{
        std::unique_ptr<Server> IRCserver = std::make_unique<Server>(port, password);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
	return 0;
}
