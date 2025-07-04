#ifndef MATHCLASSROOM_H
#define MATHCLASSROOM_H

#include "model/ClassRoomType.h"


/**
 * @brief Represents a classroom type specifically for math classes.
 *
 * The MathClassRoom class is a derived class of ClassRoomType, tailored for math classrooms.
 * It includes an additional attribute to indicate the presence of formulas tables and implements
 * the required virtual functions to calculate rent costs and provide type-specific information.
 */
class MathClassRoom final : public ClassRoomType {
private:
    bool formulasTables; /**< Indicates whether the math classroom has formulas tables available. */

public:
    /**
     * @brief Constructs a MathClassRoom object.
     *
     * @param formulasTables Specifies whether the classroom has formulas tables (default is false).
     */
    explicit MathClassRoom(bool formulasTables = false);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the MathClassRoom object.
     */
    ~MathClassRoom() override = default;

    /**
     * @brief Checks if the classroom has formulas tables.
     *
     * @return True if formulas tables are available, false otherwise.
     */
    [[nodiscard]] bool isFormulasTables() const;

    /**
     * @brief Retrieves the type identifier of the classroom.
     *
     * @return The string "MATH", indicating a math classroom type.
     */
    [[nodiscard]] std::string getType() const override;

    /**
     * @brief Calculates the rent cost for the math classroom.
     *
     * The rent cost is the base price, with an additional $15 if formulas tables are available.
     *
     * @param price The base price to use in the rent cost calculation.
     * @return The calculated rent cost.
     */
    [[nodiscard]] double calculateRentCosts(double price) const override;

    /**
     * @brief Retrieves a formatted string with information about the math classroom.
     *
     * The string includes the classroom type and whether formulas tables are available.
     *
     * @return A string containing the classroom's information.
     */
    [[nodiscard]] std::string getInfo() const override;

    /**
     * @brief Retrieves a comma-separated string of the classroom's attributes.
     *
     * The string includes the classroom type ("MATH") and the formulas tables status.
     *
     * @return A comma-separated string of the classroom's attributes.
     */
    [[nodiscard]] std::string getAttributes() const override;
};



#endif //MATHCLASSROOM_H
