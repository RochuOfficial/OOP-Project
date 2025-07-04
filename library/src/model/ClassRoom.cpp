#include "model/ClassRoom.h"
#include "model/ClassRoomType.h"
#include <sstream>
#include <utility>


ClassRoom::ClassRoom(const int number, const bool available, const int seatsNumber, const double rentCost, ClassRoomTypePtr  classRoomType)
    : number(number), available(available), seatsNumber(seatsNumber), rentCost(rentCost), classRoomType(std::move(classRoomType))
{}

int ClassRoom::getNumber() const{
    return number;
}

bool ClassRoom::isAvailable() const{
    return available;
}

int ClassRoom::getSeatsNumber() const{
    return seatsNumber;
}

double ClassRoom::getRentCost() const {
    return rentCost;
}

double ClassRoom::getActualRentCost() const{
    return getClassRoomType()->calculateRentCosts(getRentCost());
}

ClassRoomTypePtr ClassRoom::getClassRoomType() const{
    return classRoomType;
}

void ClassRoom::setNumber(const int newNumber){
    if (newNumber > 0){
        number = newNumber;
    }
}

void ClassRoom::setRentCost(const double newRentCost) {
    if (newRentCost > 0) {
        rentCost = newRentCost;
    }
}

void ClassRoom::setAvailable(const bool newAvailable){
    available = newAvailable;
}

void ClassRoom::setSeatsNumber(const int newSeatsNumber){
    if (newSeatsNumber > 0){
        seatsNumber = newSeatsNumber;
    }
}

std::string ClassRoom::getInfo() const{
    std::stringstream ss;

    ss << "ClassRoom number: " << getNumber();
    ss << ", available: " << isAvailable();
    ss << ", seatsNumber: " << getSeatsNumber();
    ss << ", " << classRoomType->getInfo();

    return ss.str();
}

std::string ClassRoom::getAttributes() const {
    std::stringstream ss;

    ss << getNumber() << "," << isAvailable() << "," << getSeatsNumber() << "," << getRentCost() << "," << getClassRoomType()->getAttributes();

    return ss.str();
}
