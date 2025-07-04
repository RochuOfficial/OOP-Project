#include "model/ITClassRoom.h"
#include <sstream>


ITClassRoom::ITClassRoom(const int computerCount)
    : computerCount(computerCount)
{
}

int ITClassRoom::getComputerCount() const {
    return computerCount;
}

std::string ITClassRoom::getType() const {
    return "IT";
}

std::string ITClassRoom::getAttributes() const {
    std::stringstream ss;

    ss << getType() << "," << getComputerCount();

    return ss.str();
}

double ITClassRoom::calculateRentCosts(const double price) const {
    if (computerCount > 0) {
        return price * 1.5 * computerCount / 10;
    }

    return price * 1.5;;
}

std::string ITClassRoom::getInfo() const {
    std::stringstream ss;

    ss << "IT class, ";
    ss << "Computers: " << getComputerCount();

    return ss.str();
}
