#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Utils.hpp"

class Client {
public:
    Client(int socket);
    void handleClient();
	//setters
    void setIP(std::string ip);
    void setPort(std::string port);
	void setNick(std::string nick);
	void setUsername(std::string username);
	void setRealname(std::string realname);
	//getters
    int getSocket();
	const std::string &getIP();
	const std::string &getPort();
    const std::string &getNick();
	const std::string &getUsername();
    const std::string &getRealname();
    
private:
    int _socket;
	std::string _ip;
	std::string _port;
	std::string _nick;
	std::string _username;
	std::string _realname;
};

#endif // !CLIENT_HPP
