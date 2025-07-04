#ifndef CLASSROOMREPOSITORY_H
#define CLASSROOMREPOSITORY_H

#include "model/ClassRoom.h"
#include "typedefs.h"
#include <vector>
#include <string>


/**
 * @brief Manages a collection of ClassRoom objects.
 *
 * The ClassRoomRepository class provides functionality to store, retrieve, and manipulate
 * a collection of classrooms. It supports operations such as adding and removing classrooms,
 * finding classrooms by number or custom criteria, and querying the size of the collection.
 */
class ClassRoomRepository {
private:
    std::vector<ClassRoomPtr> rooms; /**< Collection of shared pointers to ClassRoom objects. */

public:
    /**
     * @brief Default constructor.
     *
     * Initializes an empty ClassRoomRepository.
     */
    ClassRoomRepository() = default;

    /**
     * @brief Default destructor.
     *
     * Ensures proper cleanup of the ClassRoomRepository object.
     */
    ~ClassRoomRepository() = default;

    /**
     * @brief Finds a classroom by its unique number.
     *
     * Searches the repository for a classroom with the specified number.
     *
     * @param number The unique number of the classroom to find.
     * @return A shared pointer to the found ClassRoom, or nullptr if no matching classroom is found.
     */
    [[nodiscard]] ClassRoomPtr findClassRoomByNumber(int number) const;

    /**
     * @brief Adds a classroom to the repository.
     *
     * The classroom is added only if the provided pointer is not null.
     *
     * @param classRoom Shared pointer to the ClassRoom to add.
     */
    void add(const ClassRoomPtr& classRoom);

    /**
     * @brief Removes a classroom from the repository.
     *
     * The classroom is removed only if the provided pointer is not null.
     *
     * @param classRoom Shared pointer to the ClassRoom to remove.
     */
    void remove(const ClassRoomPtr& classRoom);

    /**
     * @brief Gets the number of classrooms in the repository.
     *
     * @return The number of classrooms as an integer.
     */
    [[nodiscard]] int size() const;

    /**
     * @brief Retrieves all classrooms in the repository.
     *
     * @return A vector of shared pointers to all ClassRoom objects.
     */
    [[nodiscard]] std::vector<ClassRoomPtr> findAll() const;

    /**
     * @brief Finds classrooms that satisfy a given predicate.
     *
     * Searches the repository for classrooms that match the specified predicate function.
     *
     * @param predicate A function that takes a ClassRoomPtr and returns true if the classroom matches the criteria.
     * @return A vector of shared pointers to ClassRoom objects that satisfy the predicate.
     */
    [[nodiscard]] std::vector<ClassRoomPtr> findBy(const ClassRoomPredicate& predicate) const;
};



#endif //CLASSROOMREPOSITORY_H
