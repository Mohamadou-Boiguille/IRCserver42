#include "../../includes/Client.hpp"

Client::Client(int socket) : _socket(socket) {
}


// Setters
void Client::setIP(std::string ip) {
    _ip = ip;
}

void Client::setPort(std::string port) {
    _port = port;
}

void Client::setNick(std::string nick) {
    _nick = nick;
}

void Client::setUsername(std::string username) {
    _username = username;
}

void Client::setRealname(std::string realname) {
    _realname = realname;
}

// Getters
int Client::getSocket() {
    return _socket;
}

const std::string &Client::getIP() {
    return _ip;
}

const std::string &Client::getPort() {
    return _port;
}

const std::string &Client::getNick() {
    return _nick;
}

const std::string &Client::getUsername() {
    return _username;
}

const std::string &Client::getRealname() {
    return _realname;
}
