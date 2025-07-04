#include "model/MathClassRoom.h"
#include <sstream>


MathClassRoom::MathClassRoom(const bool formulasTables)
    : formulasTables(formulasTables)
{
}

bool MathClassRoom::isFormulasTables() const {
    return formulasTables;
}

std::string MathClassRoom::getType() const {
    return "MATH";
}

std::string MathClassRoom::getAttributes() const {
    std::stringstream ss;

    ss << getType() << "," << isFormulasTables();

    return ss.str();
}

double MathClassRoom::calculateRentCosts(const double price) const {
    if (isFormulasTables()) {
        return price + 15;
    }

    return price;
}

std::string MathClassRoom::getInfo() const {
    std::stringstream ss;

    ss << "Math class, ";
    ss<< "FormulasTables: " << isFormulasTables();

    return ss.str();
}
