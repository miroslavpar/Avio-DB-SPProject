//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_OPTIMIZECOMMAND_H
#define SDPPROJECT_OPTIMIZECOMMAND_H

#include "ICommand.h"

class OptimizeCommand: public ICommand {
public:
    OptimizeCommand(): ICommand (std::string("optimize")) {};
    void execute (TXTPlaneManager& planeManager) {
        assert(arguments.size() == 0);
        planeManager.optimize();
    }

};
#endif //SDPPROJECT_OPTIMIZECOMMAND_H
