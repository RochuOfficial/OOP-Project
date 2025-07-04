#include "model/EngClassRoom.h"
#include <sstream>


EngClassRoom::EngClassRoom(const bool headphones)
    : headphones(headphones)
{
}

bool EngClassRoom::isHeadphones() const {
    return headphones;
}

std::string EngClassRoom::getType() const {
    return "ENG";
}

std::string EngClassRoom::getAttributes() const {
    std::stringstream ss;

    ss << getType() << "," << isHeadphones();

    return ss.str();
}

double EngClassRoom::calculateRentCosts(const double price) const {
    if (isHeadphones()) {
        return price*1.2+20;
    }

    return price*1.2;
}

std::string EngClassRoom::getInfo() const {
    std::stringstream ss;

    ss << "English class, ";
    ss << "Headphones: " << isHeadphones();

    return ss.str();
}
