#ifndef PERSONFILESTORAGE_H
#define PERSONFILESTORAGE_H

#include "repositories/PersonRepository.h"


/**
 * @brief Manages file-based storage and retrieval of Person objects.
 *
 * The PersonFilesStorage class provides functionality to save and load Person objects
 * to/from text files, as well as manage an archive of persons. It supports saving a repository
 * of persons to a file, loading persons into a repository, and handling archived person data
 * with conflict resolution for person IDs.
 */
class PersonFilesStorage {
public:
    /**
     * @brief Default constructor.
     *
     * Initializes a PersonFilesStorage object.
     */
    PersonFilesStorage() = default;

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the PersonFilesStorage object.
     */
    ~PersonFilesStorage() = default;

    /**
     * @brief Saves all persons from a repository to a file.
     *
     * Writes the attributes of all persons in the repository to a text file located at
     * "./../../database/students/Person.txt". Each person's attributes are written on a new line.
     *
     * @param personRepo Shared pointer to the PersonRepository containing the persons to save.
     * @return True if the save operation is successful, throws a std::runtime_error if the file cannot be opened.
     */
    static bool saveToFile(const PersonRepositoryPtr& personRepo);

    /**
     * @brief Loads persons from a file into a repository.
     *
     * Reads person data from "./../../database/students/Person.txt", parses each line to create
     * Person objects, and adds them to the provided repository. Skips empty lines and logs errors
     * for parsing failures.
     *
     * @param personRepo Shared pointer to the PersonRepository to populate with loaded persons.
     * @return True if the load operation is successful or the file is empty, throws a std::runtime_error if the file cannot be opened.
     */
    static bool load(PersonRepositoryPtr& personRepo);

    /**
     * @brief Saves a single person to the archive file.
     *
     * Appends the attributes of the specified person (identified by their ID) to the archive file
     * located at "./../../archive/students/Person.txt".
     *
     * @param personRepo Shared pointer to the PersonRepository containing the person.
     * @param id The unique ID of the person to archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     * @throws std::logic_error if no person with the specified ID is found.
     */
    static void saveArchive(const PersonRepositoryPtr& personRepo, int id) ;

    /**
     * @brief Loads a person from the archive and adds it to the repository.
     *
     * Retrieves a person with the specified ID from the archive file
     * ("./../../archive/students/Person.txt"). If a person with the same name exists in the
     * repository, the operation is aborted with a message. If the ID is already in use, the ID
     * is incremented to avoid conflicts. The archive file is updated to reflect the removal of
     * the loaded person.
     *
     * @param personRepo Shared pointer to the PersonRepository to add the loaded person to.
     * @param personalId The ID of the person to load from the archive.
     * @throws std::logic_error if no person with the specified ID is found in the archive.
     */
    static void loadArchive(const PersonRepositoryPtr& personRepo, int personalId);

    /**
     * @brief Saves a collection of persons to the archive file.
     *
     * Writes the attributes of the provided persons to the archive file
     * ("./../../archive/students/Person.txt"), overwriting any existing content.
     *
     * @param persons A vector of shared pointers to Person objects to archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     */
    static void saveAllArchive(const std::vector<PersonPtr>& persons) ;

    /**
     * @brief Retrieves all persons from the archive file.
     *
     * Reads person data from "./../../archive/students/Person.txt", parses each line to create
     * Person objects, and returns them as a vector. Skips empty lines and logs errors for
     * parsing failures.
     *
     * @return A vector of shared pointers to Person objects loaded from the archive.
     * @throws std::runtime_error if the archive file cannot be opened.
     */
    static std::vector<PersonPtr> getArchive();
};



#endif //PERSONFILESTORAGE_H
