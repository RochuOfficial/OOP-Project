#ifndef INDIVIDUALLESSON_H
#define INDIVIDUALLESSON_H

#include "Lesson.h"
#include "typedefs.h"


/**
 * @brief Represents an individual lesson with a single student.
 *
 * The IndividualLesson class is a derived class of Lesson, tailored for one-on-one lessons
 * between a teacher and a single student. It extends the base Lesson class by including a
 * student attribute and provides methods to manage the lesson's lifecycle and information.
 */
class IndividualLesson final : public Lesson {
private:
    PersonPtr student; /**< Shared pointer to the student attending the individual lesson. */

public:
    /**
     * @brief Constructs an IndividualLesson object.
     *
     * Initializes an individual lesson with the specified teacher, start time, base cost, subject,
     * classroom, and student. The student is marked as attending the lesson, and the lesson ID
     * is assigned to the student. Inherits initialization behavior from the Lesson base class.
     *
     * @param teacher Shared pointer to the teacher conducting the lesson.
     * @param beginTime The start time of the lesson (as a boost::posix_time::ptime).
     * @param endTime The end time of the lesson (as a boost::posix_time::ptime).
     * @param baseCost The base cost per hour for the lesson (must be non-negative).
     * @param subject The subject of the lesson.
     * @param classRoom Shared pointer to the classroom where the lesson takes place.
     * @param student Shared pointer to the student attending the lesson.
     */
    IndividualLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom, const PersonPtr &student);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the IndividualLesson object.
     */
    ~IndividualLesson() override;

    /**
     * @brief Gets the student attending the lesson.
     *
     * @return Shared pointer to the student.
     */
    [[nodiscard]] PersonPtr getStudent() const;

    /**
     * @brief Gets the teacher conducting the lesson.
     *
     * @return Shared pointer to the teacher, inherited from the Lesson base class.
     */
    [[nodiscard]] PersonPtr getTeacher() const override;

    /**
     * @brief Gets the start time of the lesson.
     *
     * @return The start time as a boost::posix_time::ptime, inherited from the Lesson base class.
     */
    [[nodiscard]] pt::ptime getBeginTime() const override;

    /**
     * @brief Gets the end time of the lesson.
     *
     * @return The end time as a boost::posix_time::ptime, inherited from the Lesson base class.
     */
    [[nodiscard]] pt::ptime getEndTime() const override;

    /**
     * @brief Gets the base cost per hour of the lesson.
     *
     * @return The base cost, inherited from the Lesson base class.
     */
    [[nodiscard]] int getBaseCost() const override;

    /**
     * @brief Gets the subject of the lesson.
     *
     * @return The subject as a string, inherited from the Lesson base class.
     */
    [[nodiscard]] std::string getSubject() const override;

    /**
     * @brief Gets the classroom where the lesson takes place.
     *
     * @return Shared pointer to the classroom, inherited from the Lesson base class.
     */
    [[nodiscard]] ClassRoomPtr getClassRoom() const override;

    /**
     * @brief Gets the unique identifier of the lesson.
     *
     * @return The lesson ID, inherited from the Lesson base class.
     */
    [[nodiscard]] int getID() const override;

    /**
     * @brief Gets the total cost of the lesson.
     *
     * @return The total cost, inherited from the Lesson base class.
     */
    [[nodiscard]] long getTotalCost() const override;

    /**
     * @brief Checks if the lesson has started.
     *
     * Delegates to the base class to determine if the lesson is marked as started.
     *
     * @return True if the lesson has started, false otherwise.
     */
    [[nodiscard]] bool isStarted() const override;

    /**
     * @brief Marks the lesson as started or not started.
     *
     * Delegates to the base class to set the lesson's started status.
     *
     * @param start Boolean indicating whether the lesson is started (true) or not (false).
     */
    void startLesson(bool start) override;

    /**
     * @brief Finishes the individual lesson and updates its state.
     *
     * Calls the base class finishLesson() to update the lesson's end time, classroom, and teacher status,
     * and additionally updates the student's status to not attending.
     */
    void finishLesson() override;

    /**
     * @brief Calculates the total cost of the individual lesson.
     *
     * Delegates to the base class calculateTotalCost() to compute the cost based on lesson duration
     * and classroom rent.
     *
     * @return The calculated total cost, inherited from the Lesson base class.
     */
    [[nodiscard]] long calculateTotalCost() const override;

    /**
     * @brief Retrieves a formatted string with detailed information about the individual lesson.
     *
     * The string includes the base lesson information (from Lesson::getInfo) and the student's information.
     *
     * @return A string containing the individual lesson's information.
     */
    [[nodiscard]] std::string getInfo() const override;

    /**
     * @brief Retrieves a comma-separated string of the individual lesson's attributes.
     *
     * The string includes the lesson type ("INDIVIDUAL"), base lesson attributes (from Lesson::getAttributes),
     * and the student's attributes.
     *
     * @return A comma-separated string of the individual lesson's attributes.
     */
    [[nodiscard]] std::string getAttributes() const override;
};



#endif //INDIVIDUALLESSON_H