#ifndef CLASSROOMTYPE_H
#define CLASSROOMTYPE_H

#include <string>


/**
 * @brief Abstract base class for defining different types of classrooms.
 *
 * The ClassRoomType class serves as an interface for various classroom types, providing
 * a common structure for calculating rent costs and retrieving type-specific information.
 * Derived classes must implement the pure virtual functions to define specific behavior
 * for different classroom types.
 */
class ClassRoomType {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes a ClassRoomType object. Since this is an abstract class, this constructor
     * is typically called by derived class constructors.
     */
    ClassRoomType() = default;

    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes. Declared virtual to support polymorphic deletion.
     */
    virtual ~ClassRoomType() = 0;

    /**
     * @brief Calculates the rent cost for the classroom based on the provided base price.
     *
     * This pure virtual function must be implemented by derived classes to define how the
     * rent cost is calculated for a specific classroom type.
     *
     * @param price The base price to use in the rent cost calculation.
     * @return The calculated rent cost.
     */
    [[nodiscard]] virtual double calculateRentCosts(double price) const = 0;

    /**
     * @brief Retrieves the type identifier of the classroom.
     *
     * This pure virtual function must be implemented by derived classes to return a string
     * identifying the specific classroom type.
     *
     * @return A string representing the classroom type.
     */
    [[nodiscard]] virtual std::string getType() const = 0;

    /**
     * @brief Retrieves a formatted string with detailed information about the classroom type.
     *
     * This pure virtual function must be implemented by derived classes to provide a human-readable
     * description of the classroom type, including relevant attributes.
     *
     * @return A string containing detailed information about the classroom type.
     */
    [[nodiscard]] virtual std::string getInfo() const = 0;

    /**
     * @brief Retrieves a comma-separated string of the classroom type's attributes.
     *
     * This pure virtual function must be implemented by derived classes to return a string
     * containing the attributes of the classroom type in a comma-separated format.
     *
     * @return A comma-separated string of the classroom type's attributes.
     */
    [[nodiscard]] virtual std::string getAttributes() const = 0;
};



#endif //CLASSROOMTYPE_H
