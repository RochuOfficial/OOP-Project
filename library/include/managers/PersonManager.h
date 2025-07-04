#ifndef PERSONMANAGER_H
#define PERSONMANAGER_H

#include "repositories/PersonRepository.h"


/**
 * @brief Manages person operations using a repository and file storage.
 *
 * The PersonManager class provides a high-level interface for managing Person objects,
 * including adding, removing, retrieving, and reporting on persons (e.g., teachers or students).
 * It delegates data management to a PersonRepository and file-based storage operations to a
 * PersonFilesStorage, while also supporting archiving and retrieval of archived persons.
 */
class PersonManager {
private:
    PersonRepositoryPtr personRepo; /**< Shared pointer to the PersonRepository for managing person data. */
    PersonFilesStoragePtr personFilesStorage; /**< Shared pointer to the PersonFilesStorage for file-based operations. */

public:
    /**
     * @brief Constructs a PersonManager object.
     *
     * Initializes the manager with the specified repository and file storage objects.
     *
     * @param personRepo Shared pointer to the PersonRepository to use.
     * @param personFilesStorage Shared pointer to the PersonFileStorage to use.
     */
    PersonManager(PersonRepositoryPtr personRepo, PersonFilesStoragePtr personFilesStorage);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the PersonManager object.
     */
    ~PersonManager() = default;

    /**
     * @brief Adds a new person to the repository.
     *
     * Creates a new Person object with the specified attributes if no person with the given ID exists.
     * If a person with the ID already exists, returns the existing person.
     *
     * @param firstName The first name of the person.
     * @param lastName The last name of the person.
     * @param id The unique ID for the person.
     * @param duringLesson Indicates whether the person is currently in a lesson (default is false).
     * @param lessonId The ID of the lesson the person is participating in (default is -1).
     * @return A shared pointer to the added or existing Person.
     */
    [[nodiscard]] PersonPtr addPerson(const std::string& firstName, const std::string& lastName, int id, bool duringLesson=false, int lessonId=-1) const;

    /**
     * @brief Removes a person from the repository and archives it.
     *
     * Finds the person by their ID, archives them using saveArchive, and removes them from
     * the repository. If the person does not exist, no action is taken.
     *
     * @param id The unique ID of the person to remove.
     */
    void removePerson(int id) const;

    /**
     * @brief Retrieves a person by their ID.
     *
     * @param id The unique ID of the person to retrieve.
     * @return A shared pointer to the found Person, or nullptr if not found.
     */
    [[nodiscard]] PersonPtr getPerson(int id) const;

    /**
     * @brief Generates a report of all persons in the repository.
     *
     * Creates a formatted string containing detailed information about each person.
     *
     * @return A string containing the report of all persons.
     */
    [[nodiscard]] std::string report() const;

    /**
     * @brief Saves all persons in the repository to a file.
     *
     * Delegates to the PersonFilesStorage to save the repository's persons to a file.
     *
     * @return True if the save operation is successful, false if an error occurs.
     */
    [[nodiscard]] bool savePersons() const;

    /**
     * @brief Loads persons from a file into the repository.
     *
     * Delegates to the PersonFilesStorage to load persons from a file into the repository.
     *
     * @return True if the load operation is successful, false if an error occurs.
     */
    bool loadPersons();

    /**
     * @brief Archives a person by their ID.
     *
     * Delegates to the PersonFilesStorage to save the specified person to the archive file.
     * Logs an error message to the console if the operation fails.
     *
     * @param personalId The unique ID of the person to archive.
     */
    void saveArchive(int personalId) const;

    /**
     * @brief Loads a person from the archive into the repository.
     *
     * Delegates to the PersonFilesStorage to load the specified person from the archive file
     * into the repository. Logs an error message to the console if the operation fails.
     *
     * @param personalId The unique ID of the person to load from the archive.
     */
    void loadArchive(int personalId) const;

    /**
     * @brief Retrieves all persons from the archive.
     *
     * Delegates to the PersonFilesStorage to retrieve all persons from the archive file.
     * Returns an empty vector if an error occurs, logging the error to the console.
     *
     * @return A vector of shared pointers to Person objects loaded from the archive.
     */
    [[nodiscard]] std::vector<PersonPtr> getArchive() const;

    /**
     * @brief Retrieves all persons in the repository.
     *
     * @return A vector of shared pointers to all Person objects in the repository.
     */
    [[nodiscard]] std::vector<PersonPtr> findAllPersons() const;

    /**
     * @brief Finds persons that satisfy a given predicate.
     *
     * Searches the repository for persons that match the specified predicate function.
     *
     * @param predicate A function that takes a PersonPtr and returns true if the person matches the criteria.
     * @return A vector of shared pointers to Person objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<PersonPtr> findPersons(const PersonPredicate& predicate) const;
};



#endif //PERSONMANAGER_H
