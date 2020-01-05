//
// Created by Miroslav Parapanov on 2019-12-30.
//

#include "Plane.h"
 Plane::Plane() {
    id = 0;
    flights = 0;
    planeName = '\0';
    type = '\0';
}
Plane::Plane(unsigned long long _id, std::string &_planeNmae, std::string &_type, unsigned long long _flights) {
    id = _id;
    planeName = _planeNmae;
    type = _type;
    flights = _flights;
}
unsigned long long Plane::getId() const{
    return id;
}
unsigned long long Plane::getFlights() const{
    return flights;
}
std::string Plane::getPlaneName() const{
    return planeName;
}
std::string Plane::getPlaneType() const{
    return type;
}
void Plane::setId(unsigned long long _id) {
    id = _id;
}
void Plane::setflights(unsigned long long _flights) {
    flights = _flights;
}
void Plane::setPlaneName(std::string _planeName) {
    planeName = _planeName;
}
void Plane ::setPlaneType(std::string _type) {
    type = _type;
}