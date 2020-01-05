//
// Created by Miroslav Parapanov on 2020-01-01.
//

#ifndef SDPPROJECT_SEARCHCOMMAND_H
#define SDPPROJECT_SEARCHCOMMAND_H

#include "ICommand.h"

class SearchCommand: public ICommand {
public:
    SearchCommand(): ICommand(std::string("search")) {};
    void execute (TXTPlaneManager& planeManager) {
        assert(arguments.size() == 1);
        planeManager.searchId(std::stoull(arguments[0]));
    }
};
#endif //SDPPROJECT_SEARCHCOMMAND_H
