#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include "typedefs.h"


/**
 * @brief Represents a person (e.g., teacher or student) involved in a lesson.
 *
 * The Person class encapsulates attributes such as first name, last name, unique identifier,
 * lesson participation status, and associated lesson ID. It provides methods to access and
 * modify these attributes, as well as to retrieve formatted information about the person.
 */
class Person {
private:
    std::string firstName; /**< First name of the person. */
    std::string lastName; /**< Last name of the person. */
    int id; /**< Unique identifier for the person. */
    bool duringLesson; /**< Indicates whether the person is currently participating in a lesson. */
    int lessonId; /**< ID of the lesson the person is participating in, or -1 if not in a lesson. */
    std::vector<LessonPtr> futureLessons; /**< List of scheduled lessons the person is assigned to attend. */

public:
    /**
     * @brief Constructs a Person object.
     *
     * Initializes a person with the specified name, ID, and lesson participation status.
     *
     * @param firstName The first name of the person.
     * @param lastName The last name of the person.
     * @param id The unique identifier for the person (must be non-negative).
     * @param duringLesson Indicates whether the person is currently in a lesson (default is false).
     * @param lessonId The ID of the lesson the person is participating in (default is -1).
     */
    Person(std::string firstName, std::string lastName, int id, bool duringLesson = false, int lessonId = -1);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the Person object.
     */
    ~Person() = default;

    /**
     * @brief Gets the first name of the person.
     *
     * @return The first name as a string.
     */
    [[nodiscard]] std::string getFirstName() const;

    /**
     * @brief Gets the last name of the person.
     *
     * @return The last name as a string.
     */
    [[nodiscard]] std::string getLastName() const;

    /**
     * @brief Gets the unique identifier of the person.
     *
     * @return The person's ID.
     */
    [[nodiscard]] int getId() const;

    /**
     * @brief Checks if the person is currently participating in a lesson.
     *
     * @return True if the person is in a lesson, false otherwise.
     */
    [[nodiscard]] bool isDuringLesson() const;

    /**
     * @brief Gets the ID of the lesson the person is participating in.
     *
     * @return The lesson ID, or -1 if the person is not in a lesson.
     */
    [[nodiscard]] int getLessonId() const;

    /**
     * @brief Sets the lesson participation status of the person.
     *
     * @param newDuringLesson The new participation status (true for in a lesson, false otherwise).
     */
    void setDuringLesson(bool newDuringLesson);

    /**
     * @brief Sets the ID of the lesson the person is participating in.
     *
     * The lesson ID is updated only if the provided value is non-negative.
     *
     * @param newLessonId The new lesson ID.
     */
    void setLessonId(int newLessonId);

    /**
     * @brief Sets the unique identifier of the person.
     *
     * The ID is updated only if the provided value is non-negative.
     *
     * @param newId The new ID for the person.
     */
    void setId(int newId);

    /**
     * @brief Adds a lesson to the person's list of future lessons.
     *
     * Appends the specified lesson to the person's future lessons if the lesson pointer is not null.
     *
     * @param newFutureLesson Shared pointer to the lesson to add to the person's future lessons.
     */
    void addFutureLesson(const LessonPtr& newFutureLesson);

    /**
     * @brief Removes a lesson from the person's list of future lessons.
     *
     * Removes the specified lesson from the person's future lessons if the lesson pointer is not null.
     *
     * @param futureLesson Shared pointer to the lesson to remove from the person's future lessons.
     * @return 0 on success, 1 if the lesson pointer is null.
     */
    int removeFutureLesson(const LessonPtr& futureLesson);

    /**
     * @brief Retrieves the list of future lessons the person is assigned to.
     *
     * @return A vector of shared pointers to Lesson objects representing the person's future lessons.
     */
    [[nodiscard]] std::vector<LessonPtr> getFutureLessons() const;

    /**
     * @brief Retrieves a formatted string with detailed information about the person.
     *
     * The string includes the person's ID, first name, last name, lesson participation status,
     * and lesson ID (if applicable).
     *
     * @return A string containing the person's information.
     */
    [[nodiscard]] std::string getInfo() const;

    /**
     * @brief Retrieves a comma-separated string of the person's attributes.
     *
     * The string includes the first name, last name, ID, lesson participation status,
     * and lesson ID.
     *
     * @return A comma-separated string of the person's attributes.
     */
    [[nodiscard]] std::string getAttributes() const;
};



#endif //PERSON_H