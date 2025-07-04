#ifndef LESSONREPOSITORY_H
#define LESSONREPOSITORY_H

#include <vector>
#include "model/Lesson.h"


/**
 * @brief Manages a collection of Lesson objects.
 *
 * The LessonRepository class provides functionality to store, retrieve, and manipulate
 * a collection of lessons. It supports operations such as adding and removing lessons,
 * finding lessons by index, ID, or custom criteria, and querying the size of the collection.
 */
class LessonRepository {
private:
    std::vector<LessonPtr> startedLessons; /**< Collection of shared pointers to Lesson objects that have started. */
    std::vector<LessonPtr> plannedLessons; /**< Collection of shared pointers to Lesson objects that are scheduled but not yet started. */

public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty LessonRepository.
     */
    LessonRepository() = default;

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the LessonRepository object.
     */
    ~LessonRepository() = default;

    /**
     * @brief Retrieves a lesson by its index in the repository.
     *
     * @param index The index of the lesson in the repository (must be non-negative and less than the size of the repository).
     * @return A shared pointer to the Lesson at the specified index, or nullptr if the index is invalid.
     */
    LessonPtr getByIndex(const int &index);

    /**
     * @brief Retrieves a lesson by comparing it to an existing Lesson pointer.
     *
     * Searches the repository for a lesson that matches the provided Lesson pointer.
     *
     * @param lesson Shared pointer to the Lesson to find.
     * @return A shared pointer to the matching Lesson, or nullptr if the lesson is null or not found.
     */
    [[nodiscard]] LessonPtr get(const LessonPtr &lesson) const;

    /**
     * @brief Retrieves all started lessons in the repository.
     *
     * @return A vector of shared pointers to Lesson objects that have started.
     */
    [[nodiscard]] std::vector<LessonPtr> getStartedLessons() const;

    /**
     * @brief Retrieves all planned lessons in the repository.
     *
     * @return A vector of shared pointers to Lesson objects that are scheduled but not yet started.
     */
    [[nodiscard]] std::vector<LessonPtr> getPlannedLessons() const;

    /**
     * @brief Retrieves all lessons in the repository.
     *
     * @return A vector of shared pointers to all Lesson objects.
     */
    [[nodiscard]] std::vector<LessonPtr> findAll() const;

    /**
     * @brief Finds lessons that satisfy a given predicate.
     *
     * Searches the repository for lessons that match the specified predicate function.
     *
     * @param predicate A function that takes a LessonPtr and returns true if the lesson matches the criteria.
     * @return A vector of shared pointers to Lesson objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<LessonPtr> findBy(const LessonPredicate& predicate) const;

    /**
     * @brief Finds a lesson by its unique ID.
     *
     * Searches the repository for a lesson with the specified ID.
     *
     * @param index The unique ID of the lesson to find.
     * @return A shared pointer to the found Lesson, or nullptr if no matching lesson is found.
     */
    [[nodiscard]] LessonPtr findByIndex(int index) const;

    /**
     * @brief Removes a lesson from the repository.
     *
     * The lesson is removed only if the provided pointer is not null and the lesson exists in the repository.
     *
     * @param lesson Shared pointer to the Lesson to remove.
     * @return 0 on success, 1 if the lesson pointer is null, 2 if the lesson is not found.
     */
    int remove(const LessonPtr &lesson);

    /**
     * @brief Removes a lesson by its index in the repository.
     *
     * The lesson is removed only if the index is valid (non-negative and less than the size of the repository).
     *
     * @param index The index of the lesson to remove.
     * @return 0 on success, 1 if the index is invalid.
     */
    int removeByIndex(const int &index);

    /**
     * @brief Adds a lesson to the repository.
     *
     * The lesson is added only if the provided pointer is not null. If the lesson is starting immediately,
     * it is added to the started lessons collection; otherwise, it is added to the planned lessons collection
     * and associated with the teacher's future lessons.
     *
     * @param lesson Shared pointer to the Lesson to add.
     * @param now Indicates whether the lesson starts immediately (true) or is scheduled for the future (false).
     * @return 0 on success, 1 if the lesson pointer is null.
     */
    int add(const LessonPtr &lesson, bool now);

    /**
     * @brief Gets the number of lessons in the repository.
     *
     * Returns the size of either the started or planned lessons collection based on the provided parameter.
     *
     * @param now If true, returns the number of started lessons; if false, returns the number of planned lessons.
     * @return The number of lessons as an integer.
     */
    [[nodiscard]] int size(bool now) const;

    /**
     * @brief Gets the total number of lessons in the repository.
     *
     * Returns the sum of the sizes of the started and planned lessons collections.
     *
     * @return The total number of lessons as an integer.
     */
    [[nodiscard]] int totalSize() const;
};



#endif //LESSONREPOSITORY_H