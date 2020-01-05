//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_DELETECOMMAND_H
#define SDPPROJECT_DELETECOMMAND_H

#include "ICommand.h"

class DeleteCommand: public ICommand {
public:
    DeleteCommand():ICommand(std::string("delete")) {};
    void execute (TXTPlaneManager& planeManager) {
        assert(arguments.size() == 1);
        planeManager.deleteById(std::stoull(arguments[0]));
    }
};
#endif //SDPPROJECT_DELETECOMMAND_H
