//
// Created by Miroslav Parapanov on 2020-01-02.
//

#ifndef SDPPROJECT_IPLANEMANAGER_H
#define SDPPROJECT_IPLANEMANAGER_H
#include <string>
class IPlaneManager {
public:
    virtual void create(unsigned long long , std::string &,
                        std::string &, unsigned long long) = 0;
    virtual void deleteById (unsigned long long ) = 0;
    virtual void show (unsigned long long, unsigned long long ) = 0;
    virtual void searchId (unsigned long long ) = 0;
    virtual void exitFromProgram() = 0;
    virtual void updateDb (unsigned long long id, std::string &, std::string&) = 0;
    virtual void optimize() = 0;
};
#endif //SDPPROJECT_IPLANEMANAGER_H
