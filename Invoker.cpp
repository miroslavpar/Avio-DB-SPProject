//
// Created by Miroslav Parapanov on 2020-01-01.
//
#include <iostream>
#include <sstream>
#include "Invoker.h"
#include "command/CreateCommand.h"
#include "command/DeleteCommand.h"
#include "command/ExitCommand.h"
#include "command/OptimizeCommand.h"
#include "command/SearchCommand.h"
#include "command/ShowCommand.h"
#include "command/UpdateCommand.h"
Invoker::Invoker(TXTPlaneManager &planeManager):planeManager(planeManager) {
    commands.push_back(std::make_unique<CreateCommand>());
    commands.push_back(std::make_unique<DeleteCommand>());
    commands.push_back(std::make_unique<ExitCommand>());
    commands.push_back(std::make_unique<OptimizeCommand>());
    commands.push_back(std::make_unique<SearchCommand>());
    commands.push_back(std::make_unique<ShowCommand>());
    commands.push_back(std::make_unique<UpdateCommand>());
}
void Invoker::run() {
    std::string line;
    for(;;){
        std::cout << "Enter command: " << std::endl;
        std::getline(std::cin, line);
        parseLine(line);
    }
}
void Invoker::parseLine(std::string& line) {
    std::stringstream stream;
    stream << line;
    std::string commandName;
    stream >> commandName;
    std::vector<std::string> arguments;
    std::string argument;
    while(stream >> argument) {
        arguments.push_back(argument);
    }
    applyArguments(commandName, arguments);
}
void Invoker::applyArguments(const std::string &commandName, std::vector<std::string> arguments) {
    for(auto& command: commands) {
        if(command->convertToString() == commandName) {
            command->setArguments(arguments);
            command->execute(planeManager);
        }
    }
}
