#ifndef CLASSROOMMANAGER_H
#define CLASSROOMMANAGER_H

#include "repositories/ClassRoomRepository.h"


/**
 * @brief Manages classroom operations using a repository and file storage.
 *
 * The ClassRoomManager class provides a high-level interface for managing ClassRoom objects,
 * including adding, removing, retrieving, and reporting on classrooms. It delegates data
 * storage to a ClassRoomFileStorage object and data management to a ClassRoomRepository object.
 * It also supports archiving classrooms and retrieving archived data.
 */
class ClassRoomManager {
private:
    ClassRoomRepositoryPtr classRoomRepo; /**< Shared pointer to the ClassRoomRepository for managing classroom data. */
    ClassRoomFilesStoragePtr classRoomFilesStorage; /**< Shared pointer to the ClassRoomFileStorage for file-based operations. */

public:
    /**
     * @brief Constructs a ClassRoomManager object.
     *
     * Initializes the manager with the specified repository and file storage objects.
     *
     * @param classRoomRepo Shared pointer to the ClassRoomRepository to use.
     * @param classRoomFilesStorage Shared pointer to the ClassRoomFileStorage to use.
     */
    ClassRoomManager(ClassRoomRepositoryPtr classRoomRepo, ClassRoomFilesStoragePtr classRoomFilesStorage);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the ClassRoomManager object.
     */
    ~ClassRoomManager() = default;

    /**
     * @brief Retrieves a classroom by its unique number.
     *
     * @param number The unique number of the classroom to retrieve.
     * @return A shared pointer to the found ClassRoom, or nullptr if not found.
     */
    [[nodiscard]] ClassRoomPtr getClassRoom(int number) const;

    /**
     * @brief Adds a new classroom to the repository.
     *
     * Creates a new ClassRoom object with the specified attributes if no classroom with the given
     * number exists. If a classroom with the number already exists, returns the existing classroom.
     *
     * @param number The unique number for the classroom.
     * @param available The availability status of the classroom.
     * @param seatsNumber The number of seats in the classroom.
     * @param rentCost The base rent cost for the classroom.
     * @param classRoomType Shared pointer to the ClassRoomType defining the classroom's type.
     * @return A shared pointer to the added or existing ClassRoom.
     */
    [[nodiscard]] ClassRoomPtr addClassRoom(int number, bool available, int seatsNumber, double rentCost, const ClassRoomTypePtr& classRoomType) const;

    /**
     * @brief Saves all classrooms in the repository to a file.
     *
     * Delegates to the ClassRoomFileStorage to save the repository's classrooms to a file.
     *
     * @return True if the save operation is successful, false if an error occurs.
     */
    [[nodiscard]] bool saveClassRooms() const;

    /**
     * @brief Loads classrooms from a file into the repository.
     *
     * Delegates to the ClassRoomFileStorage to load classrooms from a file into the repository.
     *
     * @return True if the load operation is successful, false if an error occurs.
     */
    bool loadClassRooms();

    /**
     * @brief Removes a classroom from the repository and archives it.
     *
     * Finds the classroom by its number, archives it using saveArchive, and removes it from
     * the repository. If the classroom does not exist, no action is taken.
     *
     * @param number The unique number of the classroom to remove.
     */
    void removeClassRoom(int number) const;

    /**
     * @brief Generates a report of all classrooms in the repository.
     *
     * Creates a formatted string containing information about each classroom, including
     * its number and details.
     *
     * @return A string containing the report of all classrooms.
     */
    [[nodiscard]] std::string report() const;

    /**
     * @brief Archives a classroom by its number.
     *
     * Delegates to the ClassRoomFileStorage to save the specified classroom to the archive file.
     * Logs an error message to the console if the operation fails.
     *
     * @param classRoomNumber The unique number of the classroom to archive.
     */
    void saveArchive(int classRoomNumber) const;

    /**
     * @brief Loads a classroom from the archive into the repository.
     *
     * Delegates to the ClassRoomFileStorage to load the specified classroom from the archive
     * file into the repository. Logs an error message to the console if the operation fails.
     *
     * @param classRoomNumber The unique number of the classroom to load from the archive.
     */
    void loadArchive(int classRoomNumber) const;

    /**
     * @brief Retrieves all classrooms from the archive.
     *
     * Delegates to the ClassRoomFileStorage to retrieve all classrooms from the archive file.
     * Returns an empty vector if an error occurs, logging the error to the console.
     *
     * @return A vector of shared pointers to ClassRoom objects loaded from the archive.
     */
    [[nodiscard]] std::vector<ClassRoomPtr> getArchive() const;

    /**
     * @brief Finds classrooms that satisfy a given predicate.
     *
     * Searches the repository for classrooms that match the specified predicate function.
     *
     * @param predicate A function that takes a ClassRoomPtr and returns true if the classroom matches the criteria.
     * @return A vector of shared pointers to ClassRoom objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<ClassRoomPtr> findClassRooms(const ClassRoomPredicate& predicate) const;

    /**
     * @brief Retrieves all classrooms in the repository.
     *
     * @return A vector of shared pointers to all ClassRoom objects in the repository.
     */
    [[nodiscard]] std::vector<ClassRoomPtr> findAllClassRooms() const;
};



#endif //CLASSROOMMANAGER_H
