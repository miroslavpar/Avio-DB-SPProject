//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_EXITCOMMAND_H
#define SDPPROJECT_EXITCOMMAND_H

#include "ICommand.h"

class ExitCommand: public ICommand {
public:
    ExitCommand(): ICommand(std::string ("exit")) {}
    void execute(TXTPlaneManager& planeManager) {
        assert(arguments.size() == 0);
        planeManager.exitFromProgram();
    }
};
#endif //SDPPROJECT_EXITCOMMAND_H
