//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_UPDATECOMMAND_H
#define SDPPROJECT_UPDATECOMMAND_H

#include "ICommand.h"

class UpdateCommand: public ICommand {
public:
    UpdateCommand(): ICommand (std::string("update")) {}
    void execute(TXTPlaneManager& planeManager) {
        assert(arguments.size() == 3);
        planeManager.updateDb(std::stoull(arguments[0]), arguments[1], arguments[2]);
    }
};
#endif //SDPPROJECT_UPDATECOMMAND_H
