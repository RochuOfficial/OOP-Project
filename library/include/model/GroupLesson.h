#ifndef GROUPLESSON_H
#define GROUPLESSON_H

#include <vector>
#include "Lesson.h"
#include "typedefs.h"


/**
 * @brief Represents a group lesson with multiple students.
 *
 * The GroupLesson class is a derived class of Lesson, extending its functionality to manage
 * a group of students attending the lesson. It includes methods to add and remove students,
 * calculate costs, and provide detailed information about the lesson and its participants.
 */
class GroupLesson final : public Lesson {
private:
    std::vector<PersonPtr> students; /**< List of students attending the group lesson. */

public:
    /**
     * @brief Constructs a GroupLesson object.
     *
     * Initializes a group lesson with the specified teacher, start time, base cost, subject,
     * and classroom. Inherits initialization behavior from the Lesson base class.
     *
     * @param teacher Shared pointer to the teacher conducting the lesson.
     * @param beginTime The start time of the lesson (as a boost::posix_time::ptime).
     * @param endTime The end time of the lesson (as a boost::posix_time::ptime).
     * @param baseCost The base cost per hour for the lesson (must be non-negative).
     * @param subject The subject of the lesson.
     * @param classRoom Shared pointer to the classroom where the lesson takes place.
     */
    GroupLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the GroupLesson object.
     */
    ~GroupLesson() override;

    /**
     * @brief Gets the list of students attending the lesson.
     *
     * @return A vector of shared pointers to the students.
     */
    [[nodiscard]] std::vector<PersonPtr> getStudents() const;

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
     * @brief Adds a student to the group lesson.
     *
     * Marks the student as attending the lesson and assigns the lesson ID to the student.
     *
     * @param student Shared pointer to the student to add.
     * @return 0 on success, 1 if the student pointer is null.
     */
    int addStudent(const PersonPtr &student);

    /**
     * @brief Removes a student from the group lesson.
     *
     * Removes the student from the lesson and updates their status to not attending.
     *
     * @param student Shared pointer to the student to remove.
     * @return 0 on success, 1 if the student pointer is null, 2 if the student is not attending the lesson.
     */
    int removeStudent(const PersonPtr &student);

    /**
     * @brief Finishes the group lesson and updates its state.
     *
     * Calls the base class finishLesson() to update the lesson's end time, classroom, and teacher status,
     * and additionally updates the status of all students to not attending.
     */
    void finishLesson() override;

    /**
     * @brief Calculates the total cost of the group lesson.
     *
     * Delegates to the base class calculateTotalCost() to compute the cost based on lesson duration
     * and classroom rent.
     *
     * @return The calculated total cost, inherited from the Lesson base class.
     */
    [[nodiscard]] long calculateTotalCost() const override;

    /**
     * @brief Retrieves a formatted string with detailed information about the group lesson.
     *
     * The string includes the base lesson information (from Lesson::getInfo) and a list of all students.
     *
     * @return A string containing the group lesson's information.
     */
    [[nodiscard]] std::string getInfo() const override;

    /**
     * @brief Retrieves a comma-separated string of the group lesson's attributes.
     *
     * The string includes the lesson type ("GROUP"), base lesson attributes (from Lesson::getAttributes),
     * and attributes of all students.
     *
     * @return A comma-separated string of the group lesson's attributes.
     */
    [[nodiscard]] std::string getAttributes() const override;
};



#endif //GROUPLESSON_H