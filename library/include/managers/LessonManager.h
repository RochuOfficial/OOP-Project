#ifndef LESSONMANAGER_H
#define LESSONMANAGER_H

#include "typedefs.h"
#include "model/GroupLesson.h"
#include <boost/date_time.hpp>

/**
 * @brief Namespace alias for boost::posix_time.
 */
namespace pt = boost::posix_time;


/**
 * @brief Manages lesson operations using repositories and file storage.
 *
 * The LessonManager class provides a high-level interface for managing Lesson objects,
 * including adding, removing, finishing, and reporting on lessons. It coordinates with
 * LessonRepository, PersonRepository, ClassRoomRepository, and LessonFilesStorage to
 * perform operations such as creating group or individual lessons, managing student
 * participation in group lessons, and handling file-based storage and archiving.
 */
class LessonManager {
private:
    LessonRepositoryPtr lessonRepo; /**< Shared pointer to the LessonRepository for managing lesson data. */
    LessonFilesStoragePtr lessonFilesStorage; /**< Shared pointer to the LessonFilesStorage for file-based operations. */
    PersonRepositoryPtr personRepo; /**< Shared pointer to the PersonRepository for managing person data. */
    ClassRoomRepositoryPtr classRoomRepo; /**< Shared pointer to the ClassRoomRepository for managing classroom data. */

public:
    /**
     * @brief Constructs a LessonManager object.
     *
     * Initializes the manager with the specified repositories and file storage objects.
     *
     * @param lessonRepo Shared pointer to the LessonRepository to use.
     * @param lessonFilesStorage Shared pointer to the LessonFileStorage to use.
     * @param personRepo Shared pointer to the PersonRepository to use.
     * @param classRoomRepo Shared pointer to the ClassRoomRepository to use.
     */
    LessonManager(LessonRepositoryPtr lessonRepo, LessonFilesStoragePtr lessonFilesStorage, PersonRepositoryPtr personRepo,
                  ClassRoomRepositoryPtr classRoomRepo);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the LessonManager object.
     */
    ~LessonManager() = default;

    /**
     * @brief Gets the underlying lesson repository.
     *
     * @return Shared pointer to the LessonRepository.
     */
    [[nodiscard]] LessonRepositoryPtr getLessonRepo() const;

    /**
     * @brief Removes a lesson by its ID.
     *
     * Archives the lesson before removing it from the repository. If the lesson is not found,
     * no action is taken.
     *
     * @param id The unique ID of the lesson to remove.
     * @return 0 on success, 1 if the lesson is not found, non-zero if archiving fails (error logged).
     */
    [[nodiscard]] int removeLesson(const int &id) const;

    /**
     * @brief Adds a new group lesson.
     *
     * Creates a new GroupLesson object with the specified attributes and adds it to the repository.
     * If the lesson is not starting immediately, it is added to the future lessons of all associated
     * students.
     *
     * @param teacher Shared pointer to the teacher conducting the lesson.
     * @param beginTime The start time of the lesson (as a boost::posix_time::ptime).
     * @param endTime The end time of the lesson (as a boost::posix_time::ptime).
     * @param baseCost The base cost per hour for the lesson.
     * @param subject The subject of the lesson.
     * @param classRoom Shared pointer to the classroom where the lesson takes place.
     * @param now Indicates whether the lesson starts immediately (true) or is scheduled for the future (false).
     * @return Shared pointer to the newly created GroupLesson.
     */
    [[nodiscard]] LessonPtr addGroupLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom, bool now) const;

    /**
     * @brief Adds a new individual lesson.
     *
     * Creates a new IndividualLesson object with the specified attributes and adds it to the repository.
     * If the lesson is not starting immediately, it is added to the future lessons of the associated student.
     *
     * @param teacher Shared pointer to the teacher conducting the lesson.
     * @param beginTime The start time of the lesson (as a boost::posix_time::ptime).
     * @param endTime The end time of the lesson (as a boost::posix_time::ptime).
     * @param baseCost The base cost per hour for the lesson.
     * @param subject The subject of the lesson.
     * @param classRoom Shared pointer to the classroom where the lesson takes place.
     * @param individualPerson Shared pointer to the student attending the individual lesson.
     * @param now Indicates whether the lesson starts immediately (true) or is scheduled for the future (false).
     * @return Shared pointer to the newly created IndividualLesson.
     */
    [[nodiscard]] LessonPtr addIndividualLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom, const PersonPtr &individualPerson, bool now) const;

    /**
     * @brief Adds a student to a group lesson.
     *
     * Adds the specified person to the group lesson identified by the given ID.
     *
     * @param id The unique ID of the group lesson.
     * @param person Shared pointer to the person to add as a student.
     * @return 0 on success, 3 if the lesson is not found, 4 if the person is null, non-zero if adding the student fails.
     */
    [[nodiscard]] int addStudentToGroupLesson(const int &id, const PersonPtr& person) const;

    /**
     * @brief Removes a student from a group lesson.
     *
     * Removes the specified person from the group lesson identified by the given ID.
     *
     * @param id The unique ID of the group lesson.
     * @param person Shared pointer to the person to remove.
     * @return 0 on success, 3 if the lesson is not found, 4 if the person is null, 5 if the person is not in the lesson, non-zero if removing the student fails.
     */
    [[nodiscard]] int removeStudentFromGroupLesson(const int &id, const PersonPtr &person) const;

    /**
     * @brief Retrieves a lesson by its ID.
     *
     * @param id The unique ID of the lesson to retrieve.
     * @return Shared pointer to the found Lesson, or nullptr if not found.
     */
    [[nodiscard]] LessonPtr getLesson(const int &id) const;

    /**
     * @brief Generates a report of all lessons in the repository.
     *
     * Creates a formatted string containing detailed information about each lesson, numbered sequentially.
     *
     * @return A string containing the report of all lessons.
     */
    [[nodiscard]] std::string report() const;

    [[nodiscard]] bool startLesson(const int &id) const;

    /**
     * @brief Finishes a lesson and updates related entities.
     *
     * Marks the lesson as finished, updates the classroom availability, clears lesson IDs for
     * associated persons, and removes the lesson from the repository. Logs errors if the lesson
     * or classroom is not found.
     *
     * @param id The unique ID of the lesson to finish.
     * @return True if the lesson is successfully finished and removed, false if the lesson is not found.
     */
    [[nodiscard]] bool finishLesson(const int &id) const;

    /**
     * @brief Finds lessons that satisfy a given predicate.
     *
     * Searches the repository for lessons that match the specified predicate function.
     *
     * @param predicate A function that takes a LessonPtr and returns true if the lesson matches the criteria.
     * @return A vector of shared pointers to Lesson objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<LessonPtr> findLessons(const LessonPredicate& predicate) const;

    /**
     * @brief Retrieves all lessons in the repository.
     *
     * @return A vector of shared pointers to all Lesson objects in the repository.
     */
    [[nodiscard]] std::vector<LessonPtr> findAllLessons() const;

    /**
     * @brief Retrieves all started lessons in the repository.
     *
     * Queries the LessonRepository to obtain a list of all lessons that have been marked as started.
     *
     * @return A vector of shared pointers to Lesson objects that are currently started.
     */
    [[nodiscard]] std::vector<LessonPtr> findStartedLessons() const;

    /**
     * @brief Retrieves all planned lessons in the repository.
     *
     * Queries the LessonRepository to obtain a list of all lessons that are scheduled but not yet started.
     *
     * @return A vector of shared pointers to Lesson objects that are planned.
     */
    [[nodiscard]] std::vector<LessonPtr> findPlannedLessons() const;

    /**
     * @brief Saves all lessons in the repository to files.
     *
     * Delegates to the LessonFilesStorage to save the repository’s lessons to individual files.
     *
     * @return True if the save operation is successful, false if an error occurs.
     */
    [[nodiscard]] bool save() const;

    /**
     * @brief Loads lessons from a file into the repository.
     *
     * Delegates to the LessonFilesStorage to load lessons from a file into the repository.
     *
     * @return True if all load operations are successful, false if any load operation fails.
     */
    bool load();

    /**
     * @brief Archives a lesson by its ID.
     *
     * Delegates to the LessonFilesStorage to save the specified lesson to the archive file.
     * Logs an error message to the console if the operation fails.
     *
     * @param personalId The unique ID of the lesson to archive.
     */
    void saveArchive(int personalId) const;

    /**
     * @brief Displays the contents of the lesson archive file.
     *
     * Delegates to the LessonFilesStorage to print the contents of the archive file to the console.
     * Logs an error message if the operation fails.
     */
    void showArchive() const;
};



#endif //LESSONMANAGER_H