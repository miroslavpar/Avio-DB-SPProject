//
// Created by Miroslav Parapanov on 2019-12-03.
//

#ifndef SDPPROJECT_ICOMMAND_H
#define SDPPROJECT_ICOMMAND_H


#include <string>
#include <vector>
#include "../dbmanager/TXTPlaneManager.h"


class ICommand {
protected:
    std::string commandName;
    std::vector<std::string> arguments;

public:
    ICommand(){};
    ICommand(const std::string& commandNameTemp): commandName(commandNameTemp) {};
    virtual void execute(TXTPlaneManager &) {};
    void setArguments(std::vector<std::string>& arguments) {
        this->arguments = arguments;
    }
    std::string& convertToString() {
        return commandName;
    }
    virtual ~ICommand() {};
};


#endif //SDPPROJECT_ICOMMAND_H
