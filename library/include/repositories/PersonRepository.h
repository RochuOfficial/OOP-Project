#ifndef PERSONREPOSITORY_H
#define PERSONREPOSITORY_H

#include "model/Person.h"
#include "typedefs.h"
#include <vector>
#include <string>


/**
 * @brief Manages a collection of Person objects.
 *
 * The PersonRepository class provides functionality to store, retrieve, and manipulate
 * a collection of persons (e.g., teachers or students). It supports operations such as
 * adding and removing persons, finding persons by ID or custom criteria, and querying
 * the size of the collection.
 */
class PersonRepository {
private:
    std::vector<PersonPtr> persons; /**< Collection of shared pointers to Person objects. */

public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty PersonRepository.
     */
    PersonRepository() = default;

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the PersonRepository object.
     */
    ~PersonRepository() = default;

    /**
     * @brief Removes a person from the repository.
     *
     * The person is removed only if the provided pointer is not null.
     *
     * @param person Shared pointer to the Person to remove.
     */
    void remove(const PersonPtr& person);

    /**
     * @brief Adds a person to the repository.
     *
     * The person is added only if the provided pointer is not null.
     *
     * @param person Shared pointer to the Person to add.
     */
    void add(const PersonPtr& person);

    /**
     * @brief Gets the number of persons in the repository.
     *
     * @return The number of persons as an integer.
     */
    [[nodiscard]] int size() const;

    /**
     * @brief Finds a person by their unique ID.
     *
     * Searches the repository for a person with the specified ID.
     *
     * @param id The unique ID of the person to find.
     * @return A shared pointer to the found Person, or nullptr if no matching person is found.
     */
    [[nodiscard]] PersonPtr findPersonById(int id) const;

    /**
     * @brief Finds persons that satisfy a given predicate.
     *
     * Searches the repository for persons that match the specified predicate function.
     *
     * @param predicate A function that takes a PersonPtr and returns true if the person matches the criteria.
     * @return A vector of shared pointers to Person objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<PersonPtr> findBy(const PersonPredicate& predicate) const;

    /**
     * @brief Retrieves all persons in the repository.
     *
     * @return A vector of shared pointers to all Person objects.
     */
    [[nodiscard]] std::vector<PersonPtr> findAll() const;
};



#endif //PERSONREPOSITORY_H
