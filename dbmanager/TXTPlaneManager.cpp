//
// Created by Miroslav Parapanov on 2019-12-23.
//

#include "TXTPlaneManager.h"
#include "../Plane.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <sstream>

int TXTPlaneManager::binarySearch(std::vector<Plane>& idArray,
                int size, unsigned long long id) {
    int low = 0, high = size - 1;
    while(low <= high) {
        int mid = (low + high) / 2;
        if (idArray[mid].getId() == id) return mid;
        else if (idArray[mid].getId() > mid)low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
TXTPlaneManager::TXTPlaneManager(const std::string &dbFileName)
        : dbFileName(dbFileName) {}
std::vector<Plane> TXTPlaneManager::merge(std::vector<Plane> firstHalf, std::vector<Plane>secondHalf) {
    int firstHalfSize = firstHalf.size();
    int secondHalfSize = secondHalf.size();
    std::vector<Plane> mergedPlane;
    int i = 0,j = 0;
    while (mergedPlane.size() != firstHalfSize + secondHalfSize) {
        if (i == firstHalfSize) {
            mergedPlane.push_back(secondHalf[j]);
            j++;
        }
        else if(j == secondHalfSize) {
            mergedPlane.push_back(firstHalf[i]);
            i++;
        }
        else if(firstHalf[i].getId() < secondHalf[j].getId()) {
            mergedPlane.push_back(firstHalf[i]);
            i++;
        }
        else {
            mergedPlane.push_back(secondHalf[j]);
            j++;
        }
    }
    return mergedPlane;
}
std::vector<Plane> TXTPlaneManager::mergeSort(std::vector<Plane> &plane) {
    int planesCount = plane.size();
    int mid = planesCount / 2;
    if(planesCount < 2) {
        return plane;
    }
    std::vector<Plane> firstHalf;
    std::vector<Plane> secondHalf;
    for(int i  = 0 ; i < mid ; i++) {
        firstHalf.push_back(plane[i]);
    }
    for(int i  = mid ; i < planesCount ; i++) {
        secondHalf.push_back(plane[i]);
    }
    std::vector<Plane> firstHalfSorted = mergeSort(firstHalf);
    std::vector<Plane> secondHalfSorted = mergeSort(secondHalf);
    return merge(firstHalfSorted, secondHalfSorted);

}
void TXTPlaneManager::readFindAndWrite(std::fstream &dbFile, std::string &planeAttribute,
                                    unsigned long long id, const int maxBytes, const int maxPaddingBytes) {
    std::string idNum, planeName, planeType, flights, newIdInString;
    int lineCounter = 0;
    while(!dbFile.eof()) {
        dbFile >> idNum;
        if(idNum[0] == '-') {
            lineCounter++;
            continue;
        }
        dbFile >> planeName >> planeType >> flights;
        unsigned long long tempId = std::stoull(idNum);
        if(tempId == id) {
            dbFile.seekg(lineCounter * (maxDbFileLineInBytes + 1) + maxBytes);
            writeWithPadding(dbFile, planeAttribute, maxPaddingBytes);
            break;
        }
        lineCounter++;
    }

}
void TXTPlaneManager::writeWithPadding(std::fstream &oFile, std::string &value, int maxBlockSize) {
    int valueInBytes = value.length();
    oFile << value;
    int padding = maxBlockSize - valueInBytes + 1;
    for(int i = 0 ; i < padding ; i++) {
        oFile << ' ';
    }
}
void TXTPlaneManager::create(unsigned long long id, std::string &planeName,
        std::string &type, unsigned long long flights) {

    if (id <= 0 || id > pow(2, 50)) {
        std::cout << "Invalid ID"<<std::endl;
        return;
    }
    if (flights <= 0 || flights > pow(2, 50)) {
        std::cout << "Invalid flights"<<std::endl;
        return;
    }
    std::fstream oFile;
    oFile.open(dbFileName, std::ios::app);

    //ID
    std::string idInString;
    std::stringstream stream;
    stream << id;
    stream >> idInString;
    writeWithPadding(oFile, idInString, maxIdBytes);

    //PlaneName
    writeWithPadding(oFile, planeName, maxPlaneNameBytes);

    //PlaneType
    writeWithPadding(oFile, type, maxPlaneTypeBytes);

    //Flights
    std::string flightsInString;
    stream.clear();
    stream << flights;
    stream >> flightsInString;
    writeWithPadding(oFile, flightsInString, maxFlightsBytes);

    oFile << '\n';
    oFile.close();
}
void TXTPlaneManager::deleteById(unsigned long long id) {
    std::fstream dbFile(dbFileName);
    std::string idNum, planeName, type, flights;
    unsigned long long tempId = 0;
    int lineCounter = 0;
    while(!dbFile.eof()) {
        dbFile >> idNum ;
        if(idNum[0] == '-') continue;
        dbFile >> planeName >> type >> flights;
        tempId = std::stoull(idNum);
        if(tempId == id) {
            dbFile.seekg(lineCounter * (maxDbFileLineInBytes + 1)); // +1 for the new line
            for(int i = 0 ; i < maxDbFileLineInBytes; i++) {
                dbFile << '-';
            }
            dbFile << '\n';
            break;
        }
        lineCounter++;
    }
    dbFile.close();
}
void TXTPlaneManager::show(unsigned long long offset, unsigned long long limit) {
    std::ifstream dbFile(dbFileName);
    std::string idNum, planeName, type, flights;
    unsigned long long lineCounter = 1;
    for(;;) {
        dbFile >> idNum;
        if(idNum[0] == '-')continue;
        dbFile >> planeName >> type >> flights;
        if(lineCounter - 1 == offset + limit || dbFile.eof())break;
        if(lineCounter > offset && lineCounter <= offset + limit) {
            std::cout << idNum << ' ' << planeName << ' ' << type
                    << ' ' << flights <<std::endl;
        }
        lineCounter++;
    }

}
void TXTPlaneManager::searchId(unsigned long long id) {
    std::ifstream dbFile(dbFileName);
    std::string idNum, planeName, type, flights;
    if (!isOptimizeOn) {
        unsigned long long tempId = 0;
        while (!dbFile.eof()) {
            dbFile >> idNum;
            if (idNum[0] == '-')continue;
            dbFile >> planeName >> type >> flights;
            tempId = std::stoull(idNum);
            if (tempId == id) {
                std::cout << idNum << ' ' << planeName << ' ' << type
                          << ' ' << flights << std::endl;
                break;
            }
        }
    }
    else {
        std::vector<Plane> planes;
        unsigned long long convertedId = 0;
        unsigned long long convertedFlights = 0;
        while (!dbFile.eof()) {
            Plane plane;
            dbFile >> idNum;
            if (idNum[0] == '-')continue;
            dbFile >> planeName >> type >> flights;
            convertedId = std::stoull(idNum);
            convertedFlights = std::stoull(flights);
            plane.setId(convertedId);
            plane.setPlaneName(planeName);
            plane.setPlaneType(type);
            plane.setflights(convertedFlights);
            planes.push_back(plane);
        }

        int index = binarySearch(planes, planes.size(), id);
        if (index == -1)return;
        std::cout << planes[index].getId() << ' '<< planes[index].getPlaneName() << ' '
                << planes[index].getPlaneType() << ' ' << planes[index].getFlights() << std::endl;
    }
    dbFile.close();
}
void TXTPlaneManager::exitFromProgram() {
    exit(0);
}

void TXTPlaneManager::updateId(unsigned long long id, unsigned long long newId) {
    std::fstream dbFile(dbFileName);
    std::string newIdInString;
    std::stringstream stream;
    stream << newId;
    stream >> newIdInString;
    readFindAndWrite(dbFile, newIdInString, id, 0, maxIdBytes);
    dbFile.close();
}
void TXTPlaneManager::updatePlaneName(unsigned long long id, std::string &newPlaneName) {
    std::fstream dbFile(dbFileName);
    readFindAndWrite(dbFile, newPlaneName, id, maxIdBytes + 1, maxPlaneNameBytes);
    dbFile.close();
}
void TXTPlaneManager::updatePlaneType(unsigned long long id, std::string& newPlaneType) {
    std::fstream dbFile (dbFileName);
    readFindAndWrite(dbFile, newPlaneType, id, maxIdBytes + maxPlaneNameBytes + 2, maxPlaneTypeBytes);
    dbFile.close();
}
void TXTPlaneManager::updateFlights(unsigned long long id, unsigned long long newFlights) {
    std::fstream dbFile(dbFileName);
    std::stringstream stream;
    std::string newFlightsInString;
    stream << newFlights;
    stream >> newFlightsInString;
    readFindAndWrite(dbFile, newFlightsInString, id, maxIdBytes + maxPlaneNameBytes + maxPlaneTypeBytes + 3,
                     maxFlightsBytes);
    dbFile.close();
}
void TXTPlaneManager::updateDb(unsigned long long id, std::string &attribute, std::string& changingValue) {
    std::cin >> attribute;
    if(attribute == "id") {
        unsigned  long long changingId = std::stoull(changingValue);
        updateId(id, changingId);
    }
    else if(attribute == "plane") {
        updatePlaneName(id, changingValue);
    }
    else if(attribute == "type") {
        updatePlaneType(id, changingValue);
    }
    else {
        unsigned  long long newFlights = std::stoull(changingValue);
        updateFlights(id, newFlights);
    }
}
void TXTPlaneManager::optimize() {
    std::vector<Plane> planes;
    Plane temp;
    std::ifstream dbFile (dbFileName);
    std::string id, planeName, planeType, flights;
    while (!dbFile.eof()) {
        dbFile >> id;
        if(id[0] == '-') {
            continue;
        }
        dbFile >> planeName >> planeType >> flights;
        unsigned long long idInUll = std::stoull(id);
        temp.setId(idInUll);
        temp.setPlaneName(planeName);
        temp.setPlaneType(planeType);
        unsigned long long flightsInUll = std::stoull(flights);
        temp.setflights(flightsInUll);
        planes.push_back(temp);
    }
    dbFile.close();
    std::fstream dbFileWrite(dbFileName);
    std::vector<Plane> sortedPlanes = mergeSort(planes);
    std::stringstream stream;
    std::string idInString, flightsInString;
    dbFile.seekg(0, std::ios::beg);
    for(int i = 0 ; i < sortedPlanes.size() - 1 ; i++) {
        stream << sortedPlanes[i].getId();
        stream >> idInString;
        stream.clear();
        stream << sortedPlanes[i].getFlights();
        stream >> flightsInString;
        stream.clear();
        planeName = sortedPlanes[i].getPlaneName();
        planeType = sortedPlanes[i].getPlaneType();
        writeWithPadding(dbFileWrite, idInString, maxIdBytes);
        writeWithPadding(dbFileWrite, planeName, maxPlaneNameBytes);
        writeWithPadding(dbFileWrite, planeType, maxPlaneTypeBytes);
        writeWithPadding(dbFileWrite, flightsInString, maxFlightsBytes);
        dbFileWrite << '\n';
    }
    isOptimizeOn = true;
    dbFile.close();
}

