//
// Created by Miroslav Parapanov on 2019-12-30.
//

#ifndef SDPPROJECT_PLANE_H
#define SDPPROJECT_PLANE_H

#include <string>

class Plane {
private:
    unsigned long long id;
    unsigned long long flights;
    std::string planeName;
    std::string type;
public:
    Plane();
    Plane (unsigned long long, std::string&, std::string&, unsigned long long);
    unsigned long long getId() const;
    unsigned long long getFlights() const;
    std::string getPlaneName() const;
    std::string getPlaneType() const;
    void setId(unsigned long long);
    void setflights(unsigned long long);
    void setPlaneName(std::string);
    void setPlaneType(std::string);
};


#endif //SDPPROJECT_PLANE_H
