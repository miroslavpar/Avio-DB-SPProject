//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_INVOKER_H
#define SDPPROJECT_INVOKER_H


#include <memory>
#include "command/ICommand.h"

class Invoker {
private:
    std::vector<std::unique_ptr<ICommand>> commands;
    TXTPlaneManager planeManager;
    void parseLine(std::string&);
    void applyArguments(const std::string& commandName, std::vector<std::string> arguments);
public:
    Invoker(TXTPlaneManager& planeManager);
    void run();
};


#endif //SDPPROJECT_INVOKER_H
