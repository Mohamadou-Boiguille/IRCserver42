#ifndef SERVER_START
#define SERVER_START

#include "../../includes/Server.hpp"
#include <algorithm>
#include <iostream>
#include <string>

std::shared_ptr<Client> &Server::findClientBySocket(int socket)
{
	for (auto &client : _clients)
	{
		if (client->getSocket() == socket)
			return client;
	}
	throw std::runtime_error("Client not found.");
}

std::shared_ptr<Client> &Server::findClientByName(std::string name)
{
	for (auto &client : _clients)
	{
		if (client->getNick() == name)
			return client;
	}
	throw std::runtime_error("Client not found.");
}

void Server::removeClientBySocket(int socket)
{
    auto it = std::remove_if(_clients.begin(), _clients.end(),
        [socket](const std::shared_ptr<Client>& client) {
            return client->getSocket() == socket;
        });
    for (auto toRemove = it; toRemove != _clients.end(); ++toRemove) {
        close((*toRemove)->getSocket());
    }
    _clients.erase(it, _clients.end());
}

void Server::removeClientByName(std::string nick)
{
    auto it = std::remove_if(_clients.begin(), _clients.end(),
        [nick](const std::shared_ptr<Client>& client) {
            return client->getNick() == nick;
        });
    for (auto toRemove = it; toRemove != _clients.end(); ++toRemove) {
        close((*toRemove)->getSocket());
    }
    _clients.erase(it, _clients.end());
}

void Server::acceptConnection() {
	struct sockaddr_in clientAddress;
	int newSocket;
	socklen_t clientAddressLength = sizeof(clientAddress);
	newSocket = accept(this->_serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);

	if (newSocket == -1)
		throw std::runtime_error("Failed to accept incoming connection.");
	std::shared_ptr<Client> newClient = std::make_shared<Client>(newSocket);
	_clients.push_back(newClient);
	addSocketToEpoll(newSocket);
	(*newClient).setIP(inet_ntoa(clientAddress.sin_addr));
	(*newClient).setPort(std::to_string(ntohs(clientAddress.sin_port)));
	std::cout << "Connection accepted from " << inet_ntoa(clientAddress.sin_addr) << ":"
			  << ntohs(clientAddress.sin_port) << std::endl;
}

void Server::listenToEvents() {
	struct epoll_event events[10];
	int numEvents = epoll_wait(this->_epollFd, events, 10, -1);

	for (int i = 0; i < numEvents; ++i) {
		if (events[i].data.fd == this->_serverSocket)
			acceptConnection();
		else {
			std::shared_ptr<Client> &client = findClientBySocket(events[i].data.fd);
			if (client)
				handleEvent(client);
			else
				std::cerr << "client not found." << std::endl;
		}
	}
}

void Server::handleEvent(std::shared_ptr<Client> &client) {
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	ssize_t bytesRead = recv(client->getSocket(), buffer, sizeof(buffer) - 1, 0);
	if (bytesRead == 0 || (bytesRead == -1 && errno == ECONNRESET))
	{
		int failedSocket = client->getSocket();
		removeClientBySocket(failedSocket);
		if (epoll_ctl(this->_epollFd, EPOLL_CTL_DEL, failedSocket, NULL))
			throw std::runtime_error("Failed to remove socket from epoll.");
	}
	else {
		std::string bufferString(buffer);
		std::cout << "<- " << bufferString << std::endl;
		// parseCommand(bufferString, client);
	}
}
#endif //SERVER_START
