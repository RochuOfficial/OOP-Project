#ifndef CLASSROOMUI_H
#define CLASSROOMUI_H

#include "typedefs.h"


/**
 * @brief Provides a user interface for managing classrooms.
 *
 * The ClassRoomUI class offers a console-based interface for interacting with classroom
 * operations, such as adding, removing, and displaying classrooms, as well as saving,
 * loading, and restoring classrooms from an archive. It delegates core functionality
 * to a ClassRoomManager instance.
 */
class ClassRoomUI {
private:
    ClassRoomManagerPtr classRoomManager; /**< Shared pointer to the ClassRoomManager for handling classroom operations. */

public:
    /**
     * @brief Constructs a ClassRoomUI object.
     *
     * Initializes the user interface with the specified ClassRoomManager.
     *
     * @param classRoomManager Shared pointer to the ClassRoomManager to use.
     */
    explicit ClassRoomUI(ClassRoomManagerPtr  classRoomManager);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the ClassRoomUI object.
     */
    ~ClassRoomUI() = default;

    /**
     * @brief Prompts the user to add a new classroom.
     *
     * Interactively collects input for classroom attributes (type, number, seats, rent cost,
     * and type-specific details like computers or equipment) and adds the classroom via the
     * ClassRoomManager. Validates input and ensures the classroom number is unique.
     */
    void addClassRoom() const;

    /**
     * @brief Prompts the user to remove an available classroom.
     *
     * Displays available classrooms and prompts the user to select a classroom number for
     * removal. The classroom is removed and archived via the ClassRoomManager. Handles
     * invalid inputs and unavailable classrooms.
     */
    void removeClassRoom() const;

    /**
     * @brief Displays all classrooms in the system.
     *
     * Outputs a report of all classrooms using the ClassRoomManager's report function.
     * Displays a message if no classrooms exist.
     */
    void showClassRooms() const;

    /**
     * @brief Displays all available classrooms.
     *
     * Shows a list of classrooms that are currently available. Displays a message if no
     * available classrooms exist.
     */
    void showAvailableClassRooms() const;

    /**
     * @brief Displays all classrooms in the archive.
     *
     * Shows a list of archived classrooms retrieved via the ClassRoomManager. Displays a
     * message if the archive is empty.
     */
    void showArchive() const;

    /**
     * @brief Saves all classrooms to a file.
     *
     * Delegates to the ClassRoomManager to save classrooms to a file and outputs a success
     * or failure message to the console.
     */
    void save() const;

    /**
     * @brief Loads classrooms from a file.
     *
     * Delegates to the ClassRoomManager to load classrooms from a file and outputs a success
     * or failure message to the console.
     */
    void load() const;

    /**
     * @brief Prompts the user to restore a classroom from the archive.
     *
     * Displays archived classrooms and prompts the user to select a classroom number to restore.
     * Delegates to the ClassRoomManager to load the selected classroom from the archive.
     * Handles invalid inputs and empty archives.
     */
    void restore() const;
};



#endif //CLASSROOMUI_H
