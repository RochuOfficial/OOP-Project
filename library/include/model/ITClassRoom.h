#ifndef ITCLASSROOM_H
#define ITCLASSROOM_H

#include "model/ClassRoomType.h"


/**
 * @brief Represents a classroom type specifically for IT classes.
 *
 * The ITClassRoom class is a derived class of ClassRoomType, tailored for IT classrooms.
 * It includes an additional attribute to specify the number of computers and implements
 * the required virtual functions to calculate rent costs and provide type-specific information.
 */
class ITClassRoom final : public ClassRoomType {
private:
    int computerCount; /**< Number of computers available in the IT classroom. */

public:
    /**
     * @brief Constructs an ITClassRoom object.
     *
     * @param computerCount The number of computers in the classroom (default is 0).
     */
    explicit ITClassRoom(int computerCount = 0);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the ITClassRoom object.
     */
    ~ITClassRoom() override = default;

    /**
     * @brief Gets the number of computers in the classroom.
     *
     * @return The number of computers.
     */
    [[nodiscard]] int getComputerCount() const;

    /**
     * @brief Retrieves the type identifier of the classroom.
     *
     * @return The string "IT", indicating an IT classroom type.
     */
    [[nodiscard]] std::string getType() const override;

    /**
     * @brief Calculates the rent cost for the IT classroom.
     *
     * The rent cost is calculated as 1.5 times the base price. If computers are present,
     * the cost is further scaled by the number of computers divided by 10.
     *
     * @param price The base price to use in the rent cost calculation.
     * @return The calculated rent cost.
     */
    [[nodiscard]] double calculateRentCosts(double price) const override;

    /**
     * @brief Retrieves a formatted string with information about the IT classroom.
     *
     * The string includes the classroom type and the number of computers.
     *
     * @return A string containing the classroom's information.
     */
    [[nodiscard]] std::string getInfo() const override;

    /**
     * @brief Retrieves a comma-separated string of the classroom's attributes.
     *
     * The string includes the classroom type ("IT") and the number of computers.
     *
     * @return A comma-separated string of the classroom's attributes.
     */
    [[nodiscard]] std::string getAttributes() const override;
};



#endif //ITCLASSROOM_H
