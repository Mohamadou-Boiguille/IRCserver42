#include "../../includes/Server.hpp"
Server::Server() {
}

Server::Server(std::string port, std::string password) : _host(HOST) {
	setup(port, password);
	start();
}

void Server::start()
{
	while (_serverIsRunning)
	{
		try {
			listenToEvents();
		} catch (std::exception &e) {
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
}

void Server::setup(std::string port, std::string password)
{
	validPortAndPassword(port, password);
	createServerSocket();
	bindSocket();
	listenToServerSocket();
	epollSetup();
	_serverIsRunning = true;
}

void Server::validPortAndPassword(std::string port, std::string password)
{
	if (!port.empty() && !isOnlyDigitString(port))
		throw std::invalid_argument(ERR_BADPORT);
	if (!password.empty() && !isValidPassword(password))
		throw std::invalid_argument(ERR_BADPASSWORD);
	if (port.empty())
	{
		_portNumber = 6667;
		std::cerr << "Waring: no port given! Port is default: 6667." << std::endl;
	}
	else
		_portNumber = std::stoi(port);
	if (_portNumber < 6000 || _portNumber > 7000)
		throw std::out_of_range(ERR_BADPORT);
	_password = password;
}

void Server::createServerSocket() {
	int reuse = 1;

	_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverSocket == -1)
		throw std::runtime_error("Failed to create server socket.");
	if (setsockopt(_serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1)
		throw std::runtime_error("Failed to set socket options.");
}

void Server::bindSocket()
{
	_serverAddress.sin_family = AF_INET;
	_serverAddress.sin_addr.s_addr = INADDR_ANY;
	_serverAddress.sin_port = htons(_portNumber);
	struct sockaddr *serverAddressPtr = reinterpret_cast<struct sockaddr*>(&_serverAddress);
	unsigned long structSize = sizeof (_serverAddress);

	if (bind(_serverSocket, serverAddressPtr, structSize) == -1)
		throw std::runtime_error("Failed to bind socket.");
}

void Server::listenToServerSocket() {
	int backlog = 5;

	if (listen(_serverSocket, backlog) == -1)
		throw std::runtime_error("Failed to listen thru server's socket.");
	std::cout << "Server socket created successfully" << std::endl;
}

void Server::epollSetup() {
	_epollFd = epoll_create1(0);
	if (_epollFd == -1)
		throw std::runtime_error("Failed to create epoll instance.");
	addSocketToEpoll(_serverSocket);
}

void Server::addSocketToEpoll(int socket)
{
	struct epoll_event event = {};
	event.events = EPOLLIN;
	event.data.fd = socket;
	if (epoll_ctl(this->_epollFd, EPOLL_CTL_ADD, socket, &event) == -1)
		throw std::runtime_error("Failed to add socket to epoll.");
}
Server::Server(const Server& other) {
  *this = other;
}

Server& Server::operator=(const Server& other) {
  if (this != &other) {
  }
  return *this;
}

Server::~Server() {
}
// Server::Server() {}
