#ifndef CLASSROOMFILESTORAGE_H
#define CLASSROOMFILESTORAGE_H

#include "repositories/ClassRoomRepository.h"


/**
 * @brief Manages file-based storage and retrieval of ClassRoom objects.
 *
 * The ClassRoomFilesStorage class provides functionality to save and load ClassRoom objects
 * to/from text files, as well as manage an archive of classrooms. It supports saving a repository
 * to a file, loading classrooms into a repository, and handling archived classroom data with
 * conflict resolution for classroom numbers.
 */
class ClassRoomFilesStorage {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes a ClassRoomFilesStorage object.
     */
    ClassRoomFilesStorage() = default;

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the ClassRoomFilesStorage object.
     */
    ~ClassRoomFilesStorage() = default;

    /**
     * @brief Saves all classrooms from a repository to a file.
     *
     * Writes the attributes of all classrooms in the repository to a text file located at
     * "./../../database/classrooms/Classroom.txt". Each classroom's attributes are written
     * on a new line.
     *
     * @param classRoomRepo Shared pointer to the ClassRoomRepository containing the classrooms to save.
     * @return True if the save operation is successful, throws a std::runtime_error if the file cannot be opened.
     */
    static bool saveToFile(const ClassRoomRepositoryPtr& classRoomRepo);

    /**
     * @brief Loads classrooms from a file into a repository.
     *
     * Reads classroom data from "./../../database/classrooms/Classroom.txt", parses each line
     * to create ClassRoom objects (with appropriate ClassRoomType subclasses), and adds them to
     * the provided repository. Skips invalid or empty lines and logs errors for parsing failures.
     *
     * @param classRoomRepo Shared pointer to the ClassRoomRepository to populate with loaded classrooms.
     * @return True if the load operation is successful or the file is empty, throws a std::runtime_error if the file cannot be opened.
     */
    static bool load(ClassRoomRepositoryPtr& classRoomRepo);

    /**
     * @brief Saves a single classroom to the archive file.
     *
     * Appends the attributes of the specified classroom (identified by its number) to the archive file
     * located at "./../../archive/classrooms/Classroom.txt".
     *
     * @param classRoomRepo Shared pointer to the ClassRoomRepository containing the classroom.
     * @param number The unique number of the classroom to archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     * @throws std::logic_error if no classroom with the specified number is found.
     */
    static void saveArchive(const ClassRoomRepositoryPtr& classRoomRepo, int number) ;

    /**
     * @brief Loads a classroom from the archive and adds it to the repository.
     *
     * Retrieves a classroom with the specified number from the archive file
     * ("./../../archive/classrooms/Classroom.txt"). If a classroom with the same number exists
     * in the repository, the number is incremented to avoid conflicts. Identical classrooms
     * (based on seats, rent cost, and type) are not added, and a message is logged.
     * The archive file is updated to reflect the removal of the loaded classroom.
     *
     * @param classRoomRepo Shared pointer to the ClassRoomRepository to add the loaded classroom to.
     * @param classRoomNumber The number of the classroom to load from the archive.
     * @throws std::logic_error if no classroom with the specified number is found in the archive.
     */
    static void loadArchive(const ClassRoomRepositoryPtr& classRoomRepo, int classRoomNumber);

    /**
     * @brief Saves a collection of classrooms to the archive file.
     *
     * Writes the attributes of the provided classrooms to the archive file
     * ("./../../archive/classrooms/Classroom.txt"), overwriting any existing content.
     *
     * @param classrooms A vector of shared pointers to ClassRoom objects to archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     */
    static void saveAllArchive(const std::vector<ClassRoomPtr>& classrooms) ;

    /**
     * @brief Retrieves all classrooms from the archive file.
     *
     * Reads classroom data from "./../../archive/classrooms/Classroom.txt", parses each line
     * to create ClassRoom objects (with appropriate ClassRoomType subclasses), and returns them
     * as a vector. Skips invalid or empty lines and logs errors for parsing failures.
     *
     * @return A vector of shared pointers to ClassRoom objects loaded from the archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     */
    static std::vector<ClassRoomPtr> getArchive();
};



#endif //CLASSROOMFILESTORAGE_H
