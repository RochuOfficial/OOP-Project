#ifndef LESSONUI_H
#define LESSONUI_H

#include "managers/LessonManager.h"
#include "typedefs.h"


/**
 * @brief Provides a user interface for managing lessons.
 *
 * The LessonUI class offers a console-based interface for interacting with lesson
 * operations, such as starting individual or group lessons, ending lessons, displaying
 * lessons, and managing lesson storage and archives. It delegates core functionality
 * to a LessonManager instance and coordinates with PersonManager and ClassRoomManager
 * for related operations.
 */
class LessonUI {
private:
    LessonManagerPtr manager; /**< Shared pointer to the LessonManager for handling lesson operations. */

public:
    /**
     * @brief Constructs a LessonUI object.
     *
     * Initializes the user interface with the specified LessonManager.
     *
     * @param manager Shared pointer to the LessonManager to use.
     */
    explicit LessonUI(LessonManagerPtr manager);

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the LessonUI object.
     */
    ~LessonUI() = default;

    /**
     * @brief Prompts the user to start a new lesson.
     *
     * Interactively collects input to create an individual or group lesson, including
     * teacher, student(s), classroom, start time, cost, and subject. Validates inputs
     * (e.g., ensuring available persons and classrooms) and uses the LessonManager to
     * create the lesson. Coordinates with PersonManager and ClassRoomManager to access
     * available persons and classrooms.
     *
     * @param personManager Shared pointer to the PersonManager for accessing persons.
     * @param classRoomManager Shared pointer to the ClassRoomManager for accessing classrooms.
     */
    void startLesson(const PersonManagerPtr& personManager, const ClassRoomManagerPtr& classRoomManager) const;

    /**
     * @brief Prompts the user to end a lesson.
     *
     * Displays a list of active lessons and prompts the user to select a lesson ID to end.
     * Uses the LessonManager to finish the lesson, updates related entities, and displays
     * the total cost. Handles invalid inputs and non-existent lessons.
     */
    void endLesson() const;

    /**
     * @brief Displays all active lessons.
     *
     * Shows a list of all lessons in the system using the LessonManager. Displays a
     * message if no lessons exist.
     */
    void showStartedLessons() const;

    void showPlannedLessons() const;

    /**
     * @brief Saves all lessons to files.
     *
     * Delegates to the LessonManager to save lessons to files and outputs a success or
     * failure message to the console.
     */
    void save() const;

    /**
     * @brief Loads lessons from a file.
     *
     * Delegates to the LessonManager to load lessons from a file and outputs a success
     * or failure message to the console.
     */
    void load() const;

    /**
     * @brief Displays the contents of the lesson archive.
     *
     * Delegates to the LessonManager to display the contents of the lesson archive file.
     */
    void showArchive() const;

    /**
     * @brief Starts planned lessons that are due to begin.
     *
     * Checks all planned (not yet started) lessons managed by the LessonManager and
     * starts those whose start time is earlier than the current time. Outputs an error
     * message to the console for any lesson that fails to start.
     */
    void shouldStart() const;

    /**
     * @brief Ends active lessons that are due to finish.
     *
     * Checks all active (started) lessons managed by the LessonManager and ends those
     * whose end time is earlier than the current time. Outputs an error message to the
     * console for any lesson that fails to end.
     */
    void shouldEnd() const;
};



#endif //LESSONUI_H