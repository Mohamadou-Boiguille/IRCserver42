#ifndef SERVER_HPP
#define SERVER_HPP

#include "Utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include <memory>

class Server {
public:
	Server();
	Server(std::string port, std::string password);
	~Server();

private:
	Server(const Server& other);
	Server& operator=(const Server& other);
	int					_portNumber;
	std::string			_password;
	int					_serverSocket;
	int					_epollFd;
	struct sockaddr_in	_serverAddress;
	std::string			_host;
	bool				_serverIsRunning;
	std::vector<std::shared_ptr<Client>> _clients;
	// std::vector<std::shared_ptr<Channel>> _channels;

	// setup functions
	void setup(std::string port, std::string password);
	void validPortAndPassword(std::string port, std::string password);
	void createServerSocket();
	void bindSocket();
	void listenToServerSocket();
	void epollSetup();
	void addSocketToEpoll(int socket);
	// execute functions
	void start();
	void listenToEvents();
	void acceptConnection();
	std::shared_ptr<Client> &findClientBySocket(int socket);
	std::shared_ptr<Client> &findClientByName(std::string name);
	void handleEvent(std::shared_ptr<Client> &client);
	void removeClientByName(std::string nick);
	void removeClientBySocket(int socket);
};

#endif // !SERVER_HPP
