// #ifndef COMMANDINFOS_HPP
// #define COMMANDINFOS_HPP

// #include "Client.hpp"
// #include "Utils.hpp"
// #include <memory>

// class Command {
// public:
// 	Command(std::shared_ptr<Client> sender, std::string &commandStr);
//     virtual std::string getCommandType();

// private:
// 	std::string _commandName;
// 	std::shared_ptr<Client> _sender;
// 	int _senderSocket;
// 	std::string _senderName;
// };

// Command::Command(std::shared_ptr<Client> sender, std::string &commandStr)
// 	: _senderSocket(sender->getSocket()), _senderName(sender->getNick())
// {
// 	_commandName = firstWord(commandStr);
// 	_sender = sender;
// };

// #endif //COMMANDINFOS_HPP
