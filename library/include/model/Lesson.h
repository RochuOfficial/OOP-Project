#ifndef LESSON_H
#define LESSON_H

#include "typedefs.h"
#include <boost/date_time.hpp>

/**
 * @brief Namespace alias for boost::posix_time.
 */
namespace pt = boost::posix_time;
/**
 * @brief Namespace alias for boost::date_time.
 */
namespace bdt = boost::date_time;


/**
 * @brief Abstract base class for managing lessons.
 *
 * The Lesson class encapsulates the properties and behaviors of a lesson, including the teacher,
 * start and end times, base cost, subject, and associated classroom. It provides methods to access
 * and manipulate lesson data, calculate total costs based on duration and classroom rent, and
 * manage lesson lifecycle (e.g., marking a classroom as unavailable during a lesson). Derived
 * classes may extend this functionality.
 */
class Lesson {
private:
    static int counter; /**< Static counter for generating unique lesson IDs. */
    PersonPtr teacher; /**< Shared pointer to the teacher conducting the lesson. */
    pt::ptime startTime; /**< Start time of the lesson. */
    pt::ptime endTime; /**< End time of the lesson. */
    int baseCost; /**< Base cost per hour for the lesson. */
    long totalCost; /**< Total calculated cost of the lesson (set after completion). */
    int id; /**< Unique identifier for the lesson. */
    std::string subject; /**< Subject of the lesson. */
    ClassRoomPtr classRoom; /**< Shared pointer to the classroom where the lesson takes place. */
    bool started; /**< Indicates whether the lesson has started. */

public:
    /**
     * @brief Constructs a Lesson object.
     *
     * Initializes a lesson with the specified teacher, start time, base cost, subject, and classroom.
     * The lesson ID is automatically generated, and the classroom is marked as unavailable.
     * If the provided start time is invalid, the current time is used.
     *
     * @param teacher Shared pointer to the teacher conducting the lesson.
     * @param beginTime The start time of the lesson (as a boost::posix_time::ptime).
     * @param endTime The end time of the lesson (as a boost::posix_time::ptime).
     * @param baseCost The base cost per hour for the lesson (must be non-negative).
     * @param subject The subject of the lesson.
     * @param classRoom Shared pointer to the classroom where the lesson takes place.
     */
    Lesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, std::string subject, const ClassRoomPtr &classRoom);

    /**
     * @brief Pure virtual destructor.
     *
     * Ensures proper cleanup of derived classes. Declared as pure virtual to make Lesson an abstract base class.
     */
    virtual ~Lesson() = 0;

    /**
     * @brief Gets the teacher conducting the lesson.
     *
     * @return Shared pointer to the teacher.
     */
    [[nodiscard]] virtual PersonPtr getTeacher() const;

    /**
     * @brief Gets the start time of the lesson.
     *
     * @return The start time as a boost::posix_time::ptime.
     */
    [[nodiscard]] virtual pt::ptime getBeginTime() const;

    /**
     * @brief Gets the end time of the lesson.
     *
     * @return The end time as a boost::posix_time::ptime, or not_a_date_time if the lesson is not finished.
     */
    [[nodiscard]] virtual pt::ptime getEndTime() const;

    /**
     * @brief Gets the base cost per hour of the lesson.
     *
     * @return The base cost.
     */
    [[nodiscard]] virtual int getBaseCost() const;

    /**
     * @brief Gets the subject of the lesson.
     *
     * @return The subject as a string.
     */
    [[nodiscard]] virtual std::string getSubject() const;

    /**
     * @brief Gets the classroom where the lesson takes place.
     *
     * @return Shared pointer to the classroom.
     */
    [[nodiscard]] virtual ClassRoomPtr getClassRoom() const;

    /**
     * @brief Gets the unique identifier of the lesson.
     *
     * @return The lesson ID.
     */
    [[nodiscard]] virtual int getID() const;

    /**
     * @brief Gets the total cost of the lesson.
     *
     * @return The total cost, or -1 if the lesson is not finished or invalid.
     */
    [[nodiscard]] virtual long getTotalCost() const;

    /**
     * @brief Checks if the lesson has started.
     *
     * @return True if the lesson has started, false otherwise.
     */
    [[nodiscard]] virtual bool isStarted() const;

    /**
     * @brief Marks the lesson as started or not started.
     *
     * Sets the started status of the lesson based on the provided boolean value.
     *
     * @param start Boolean indicating whether the lesson is started (true) or not (false).
     */
    virtual void startLesson(bool start);

    /**
     * @brief Finishes the lesson and updates its state.
     *
     * Sets the end time to the current time, marks the classroom as available, updates the teacher's
     * status, and calculates the total cost. If the end time is invalid (e.g., before start time),
     * the end time is reset to not_a_date_time.
     */
    virtual void finishLesson();

    /**
     * @brief Calculates the total cost of the lesson.
     *
     * The total cost is based on the lesson duration (in hours, rounded up) multiplied by the base cost,
     * plus the classroom's actual rent cost. Returns -1 if the lesson is not finished or has an invalid duration.
     * Returns 0 if the duration is less than 60 seconds.
     *
     * @return The calculated total cost.
     */
    [[nodiscard]] virtual long calculateTotalCost() const;

    /**
     * @brief Retrieves a formatted string with detailed information about the lesson.
     *
     * The string includes the lesson ID, start time, classroom information, and teacher information.
     *
     * @return A string containing the lesson's information.
     */
    [[nodiscard]] virtual std::string getInfo() const;

    /**
     * @brief Retrieves a comma-separated string of the lesson's attributes.
     *
     * The string includes the lesson ID, base cost, subject, start time, classroom attributes,
     * and teacher attributes.
     *
     * @return A comma-separated string of the lesson's attributes.
     */
    [[nodiscard]] virtual std::string getAttributes() const;
};



#endif //LESSON_H