#ifndef ENGCLASSROOM_H
#define ENGCLASSROOM_H

#include "model/ClassRoomType.h"


/**
 * @brief Represents a classroom type specifically for English classes.
 *
 * The EngClassRoom class is a derived class of ClassRoomType, tailored for English classrooms.
 * It includes an additional attribute to indicate the presence of headphones and implements
 * the required virtual functions to calculate rent costs and provide type-specific information.
 */
class EngClassRoom final : public ClassRoomType {
private:
    bool headphones; /**< Indicates whether the English classroom has headphones available. */

public:
    /**
     * @brief Constructs an EngClassRoom object.
     *
     * @param headphones Specifies whether the classroom has headphones (default is false).
     */
    explicit EngClassRoom(bool headphones = false);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the EngClassRoom object.
     */
    ~EngClassRoom() override = default;

    /**
     * @brief Checks if the classroom has headphones.
     *
     * @return True if headphones are available, false otherwise.
     */
    [[nodiscard]] bool isHeadphones() const;

    /**
     * @brief Retrieves the type identifier of the classroom.
     *
     * @return The string "ENG", indicating an English classroom type.
     */
    [[nodiscard]] std::string getType() const override;

    /**
     * @brief Calculates the rent cost for the English classroom.
     *
     * The rent cost is calculated as 1.2 times the base price, with an additional $20
     * if headphones are available.
     *
     * @param price The base price to use in the rent cost calculation.
     * @return The calculated rent cost.
     */
    [[nodiscard]] double calculateRentCosts(double price) const override;

    /**
     * @brief Retrieves a formatted string with information about the English classroom.
     *
     * The string includes the classroom type and whether headphones are available.
     *
     * @return A string containing the classroom's information.
     */
    [[nodiscard]] std::string getInfo() const override;

    /**
     * @brief Retrieves a comma-separated string of the classroom's attributes.
     *
     * The string includes the classroom type ("ENG") and the headphones status.
     *
     * @return A comma-separated string of the classroom's attributes.
     */
    [[nodiscard]] std::string getAttributes() const override;
};



#endif //ENGCLASSROOM_H
