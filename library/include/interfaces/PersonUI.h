#ifndef PERSONUI_H
#define PERSONUI_H

#include "typedefs.h"


/**
 * @brief Provides a user interface for managing persons.
 *
 * The PersonUI class offers a console-based interface for interacting with person
 * operations, such as adding, removing, and displaying persons (e.g., teachers or students),
 * as well as saving, loading, and restoring persons from an archive. It delegates core
 * functionality to a PersonManager instance.
 */
class PersonUI {
private:
    PersonManagerPtr personManager; /**< Shared pointer to the PersonManager for handling person operations. */

public:
    /**
     * @brief Constructs a PersonUI object.
     *
     * Initializes the user interface with the specified PersonManager.
     *
     * @param personManager Shared pointer to the PersonManager to use.
     */
    explicit PersonUI(const PersonManagerPtr& personManager);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the PersonUI object.
     */
    ~PersonUI() = default;

    /**
     * @brief Prompts the user to add a new person.
     *
     * Interactively collects input for person attributes (first name, last name, and ID)
     * and adds the person via the PersonManager. Validates input and ensures the ID is unique.
     */
    void addPerson() const;

    /**
     * @brief Prompts the user to remove an available person.
     *
     * Displays available persons (not currently in a lesson) and prompts the user to select
     * a person ID for removal. The person is removed and archived via the PersonManager.
     * Handles invalid inputs and unavailable persons.
     */
    void removePerson() const;

    /**
     * @brief Displays all persons in the system.
     *
     * Outputs a report of all persons using the PersonManager's report function.
     * Displays a message if no persons exist.
     */
    void showPersons() const;

    /**
     * @brief Displays all available persons.
     *
     * Shows a list of persons who are not currently in a lesson. Displays a message if
     * no available persons exist.
     */
    void showAvailablePersons() const;

    /**
     * @brief Displays all persons in the archive.
     *
     * Shows a list of archived persons retrieved via the PersonManager. Displays a message
     * if the archive is empty.
     */
    void showArchive() const;

    /**
     * @brief Saves all persons to a file.
     *
     * Delegates to the PersonManager to save persons to a file and outputs a success or
     * failure message to the console.
     */
    void save() const;

    /**
     * @brief Loads persons from a file.
     *
     * Delegates to the PersonManager to load persons from a file and outputs a success or
     * failure message to the console.
     */
    void load() const;

    /**
     * @brief Prompts the user to restore a person from the archive.
     *
     * Displays archived persons and prompts the user to select a person ID to restore.
     * Delegates to the PersonManager to load the selected person from the archive.
     * Handles invalid inputs and empty archives.
     */
    void restore() const;
};



#endif //PERSONUI_H
