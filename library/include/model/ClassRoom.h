#ifndef CLASSROOM_H
#define CLASSROOM_H

#include "typedefs.h"
#include <string>


/**
 * @brief Represents a classroom with attributes like number, availability, seating capacity, rent cost, and type.
 *
 * The ClassRoom class encapsulates the properties and behaviors of a classroom, including its identification number,
 * availability status, number of seats, base rent cost, and associated classroom type. It provides methods to access
 * and modify these attributes, as well as utility functions to retrieve formatted information about the classroom.
 */
class ClassRoom {
private:
    int number;             /**< Unique identifier for the classroom. */
    bool available;        /**< Indicates whether the classroom is available for use. */
    int seatsNumber;       /**< Number of seats available in the classroom. */
    double rentCost;       /**< Base rent cost for the classroom. */
    ClassRoomTypePtr classRoomType; /**< Pointer to the classroom type, defining additional attributes or behavior. */

public:
    /**
     * @brief Constructs a ClassRoom object with the specified attributes.
     *
     * @param number The unique identifier for the classroom (must be positive).
     * @param available The availability status of the classroom.
     * @param seatsNumber The number of seats in the classroom (must be positive).
     * @param rentCost The base rent cost for the classroom (must be positive).
     * @param classRoomType A shared pointer to the ClassRoomType object associated with this classroom.
     */
    ClassRoom(int number, bool available, int seatsNumber, double rentCost, ClassRoomTypePtr classRoomType);

    /**
     * @brief Default destructor.
     */
    ~ClassRoom() = default;

    /**
     * @brief Gets the classroom's unique identifier.
     * @return The classroom number.
     */
    [[nodiscard]] int getNumber() const;

    /**
     * @brief Checks if the classroom is available.
     * @return True if the classroom is available, false otherwise.
     */
    [[nodiscard]] bool isAvailable() const;

    /**
     * @brief Gets the number of seats in the classroom.
     * @return The number of seats.
     */
    [[nodiscard]] int getSeatsNumber() const;

    /**
     * @brief Gets the base rent cost of the classroom.
     * @return The base rent cost.
     */
    [[nodiscard]] double getRentCost() const;

    /**
     * @brief Calculates the actual rent cost based on the classroom type.
     *
     * This method delegates to the ClassRoomType's calculateRentCosts method to compute
     * the final rent cost, which may include additional factors defined by the classroom type.
     *
     * @return The actual rent cost.
     */
    [[nodiscard]] double getActualRentCost() const;

    /**
     * @brief Gets the classroom type.
     * @return A shared pointer to the ClassRoomType object.
     */
    [[nodiscard]] ClassRoomTypePtr getClassRoomType() const;

    /**
     * @brief Sets the classroom's unique identifier.
     *
     * The number is updated only if the provided value is positive.
     *
     * @param newNumber The new classroom number.
     */
    void setNumber(int newNumber);

    /**
     * @brief Sets the base rent cost of the classroom.
     *
     * The rent cost is updated only if the provided value is positive.
     *
     * @param newRentCost The new base rent cost.
     */
    void setRentCost(double newRentCost);

    /**
     * @brief Sets the availability status of the classroom.
     *
     * @param newAvailable The new availability status (true for available, false otherwise).
     */
    void setAvailable(bool newAvailable);

    /**
     * @brief Sets the number of seats in the classroom.
     *
     * The number of seats is updated only if the provided value is positive.
     *
     * @param newSeatsNumber The new number of seats.
     */
    void setSeatsNumber(int newSeatsNumber);

    /**
     * @brief Retrieves a formatted string with detailed information about the classroom.
     *
     * The string includes the classroom number, availability, number of seats, and information
     * from the associated ClassRoomType.
     *
     * @return A string containing the classroom's information.
     */
    [[nodiscard]] std::string getInfo() const;

    /**
     * @brief Retrieves a comma-separated string of the classroom's attributes.
     *
     * The string includes the classroom number, availability, number of seats, base rent cost,
     * and attributes from the associated ClassRoomType.
     *
     * @return A comma-separated string of the classroom's attributes.
     */
    [[nodiscard]] std::string getAttributes() const;
};



#endif //CLASSROOM_H