#ifndef LESSONFILESTORAGE_H
#define LESSONFILESTORAGE_H

#include "typedefs.h"


/**
 * @brief Manages file-based storage and retrieval of Lesson objects.
 *
 * The LessonFilesStorage class provides functionality to save and load Lesson objects
 * to/from text files, as well as manage an archive of lessons. It supports saving a repository
 * of lessons to individual files, loading lessons into a repository, archiving specific lessons,
 * and displaying the contents of the archive file.
 */
class LessonFilesStorage {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes a LessonFilesStorage object.
     */
    LessonFilesStorage();

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the LessonFilesStorage object.
     */
    ~LessonFilesStorage();

    /**
     * @brief Saves all lessons from a repository to individual files.
     *
     * Writes the attributes of each lesson in the repository to a separate text file named
     * "lesson-<ID>.txt", where <ID> is the lesson's unique ID.
     *
     * @param repository Shared pointer to the LessonRepository containing the lessons to save.
     * @return True if the save operation is successful, throws a std::runtime_error if a file cannot be opened.
     */
    static bool saveToFile(const LessonRepositoryPtr &repository);

    /**
     * @brief Loads lessons from a file into a repository.
     *
     * Reads lesson data from "./../../database/lessons/Lesson.txt", parses each line to create
     * Lesson objects (either IndividualLesson or GroupLesson with appropriate ClassRoomType subclasses),
     * and adds them to the provided repository. Skips empty lines and logs errors for parsing failures.
     *
     * @param repository Shared pointer to the LessonRepository to populate with loaded lessons.
     * @return True if the load operation is successful or the file is empty, throws a std::runtime_error if the file cannot be opened.
     */
    static bool load(LessonRepositoryPtr &repository);

    /**
     * @brief Saves a single lesson to the archive file.
     *
     * Appends the attributes of the specified lesson (identified by its ID) to the archive file
     * located at "./../../archive/lessons/Lesson.txt". Logs a success message to the console.
     *
     * @param lessonRepo Shared pointer to the LessonRepository containing the lesson.
     * @param id The unique ID of the lesson to archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     * @throws std::logic_error if no lesson with the specified ID is found.
     */
    static void saveArchive(const LessonRepositoryPtr& lessonRepo, int id) ;

    /**
     * @brief Displays the contents of the lesson archive file.
     *
     * Reads and prints each line from the archive file located at "./../../archive/lessons/Lesson.txt"
     * to the console.
     *
     * @throws std::runtime_error if the archive file cannot be opened.
     */
    static void showArchive();
};



#endif //LESSONFILESTORAGE_H
