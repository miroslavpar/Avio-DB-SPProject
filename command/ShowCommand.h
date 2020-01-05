//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_SHOWCOMMAND_H
#define SDPPROJECT_SHOWCOMMAND_H

#include "ICommand.h"

class ShowCommand: public ICommand {
public:
    ShowCommand(): ICommand (std::string ("show")) {};
    void execute (TXTPlaneManager& planeManager) {
        assert(arguments.size() == 2);
        planeManager.show(std::stoull(arguments[0]), std::stoull(arguments[1]));
    }
};
#endif //SDPPROJECT_SHOWCOMMAND_H
