//
// Created by Miroslav Parapanov on 2019-12-23.
//

#ifndef SDPPROJECT_TXTPLANEMANAGER_H
#define SDPPROJECT_TXTPLANEMANAGER_H

#include "../Plane.h"
#include "IPlaneManager.h"
#include <string>
#include <vector>

const int maxIdBytes = 15;
const int maxFlightsBytes = 15;
const int maxPlaneTypeBytes = 100;
const int maxPlaneNameBytes = 100;
const int maxDbFileLineInBytes = maxIdBytes + maxFlightsBytes +
                maxPlaneTypeBytes + maxPlaneNameBytes + 4;//+4 for the spaces
                //because in putPadding() we add everytime one more
static bool isOptimizeOn = false;

class TXTPlaneManager: public IPlaneManager {
private:
    const std::string dbFileName;
    void writeWithPadding(std::fstream &, std::string &, int);
    void readFindAndWrite(std::fstream &, std::string &, unsigned long long, const int, const int);
    void updateId (unsigned long long, unsigned long long);
    void updatePlaneName (unsigned long long, std::string&);
    void updatePlaneType (unsigned long long, std::string&);
    void updateFlights (unsigned long long, unsigned long long);
    std::vector<Plane> mergeSort (std::vector<Plane>&);
    std::vector<Plane> merge (std::vector<Plane>, std::vector<Plane>);
    int binarySearch(std::vector<Plane>&, int, unsigned long long);
public:
    TXTPlaneManager (const std::string &);
    void create (unsigned long long id, std::string &planeName,
                std::string &type, unsigned long long flights);

    void deleteById (unsigned long long id);
    void show (unsigned long long offset,unsigned long long limit);
    void searchId (unsigned long long id);
    void exitFromProgram();
    void updateDb (unsigned long long id, std::string &attribute, std::string& changignValue);
    void optimize();
};


#endif //SDPPROJECT_TXTPLANEMANAGER_H
