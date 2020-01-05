//
// Created by Miroslav Parapanov on 2019-12-23.
//

#ifndef SDPPROJECT_CREATECOMMAND_H
#define SDPPROJECT_CREATECOMMAND_H

#include <vector>
#include <cassert>
#include <string>
#include "ICommand.h"
#include "../Plane.h"
#include "../dbmanager/TXTPlaneManager.h"

class CreateCommand: public ICommand {
public:
    CreateCommand(): ICommand (std::string("create")) {};
    void execute(TXTPlaneManager& planeManager) {
        assert(arguments.size() == 4);
        planeManager.create(std::stoull(arguments[0]), arguments[1], arguments[2],std::stoull(arguments[3]));
    }
};


#endif //SDPPROJECT_CREATECOMMAND_H
