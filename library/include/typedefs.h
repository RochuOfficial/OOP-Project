#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <memory>
#include <functional>

/**
 * @brief Forward declarations for classes used in typedefs.
 *
 * These forward declarations allow the use of class names in typedefs without requiring
 * full class definitions, reducing compilation dependencies.
 */
class Lesson;
class IndividualLesson;
class GroupLesson;
class Person;
class ClassRoom;
class ClassRoomType;
class PersonRepository;
class ClassRoomRepository;
class LessonRepository;
class PersonFilesStorage;
class ClassRoomFilesStorage;
class LessonFilesStorage;
class PersonManager;
class ClassRoomManager;
class LessonManager;
class LessonUI;
class PersonUI;
class ClassRoomUI;

/**
 * @brief Shared pointer alias for Lesson.
 *
 * Represents a shared pointer to a Lesson object, used for managing lesson instances.
 */
typedef std::shared_ptr<Lesson> LessonPtr;

/**
 * @brief Shared pointer alias for IndividualLesson.
 *
 * Represents a shared pointer to an IndividualLesson object, a specific type of lesson.
 */
typedef std::shared_ptr<IndividualLesson> IndividualLessonPtr;

/**
 * @brief Shared pointer alias for GroupLesson.
 *
 * Represents a shared pointer to a GroupLesson object, a specific type of lesson.
 */
typedef std::shared_ptr<GroupLesson> GroupLessonPtr;

/**
 * @brief Shared pointer alias for Person.
 *
 * Represents a shared pointer to a Person object, used for managing person instances
 * (e.g., teachers or students).
 */
typedef std::shared_ptr<Person> PersonPtr;

/**
 * @brief Shared pointer alias for ClassRoom.
 *
 * Represents a shared pointer to a ClassRoom object, used for managing classroom instances.
 */
typedef std::shared_ptr<ClassRoom> ClassRoomPtr;

/**
 * @brief Shared pointer alias for ClassRoomType.
 *
 * Represents a shared pointer to a ClassRoomType object, defining specific classroom types
 * (e.g., IT, Math, or English).
 */
typedef std::shared_ptr<ClassRoomType> ClassRoomTypePtr;

/**
 * @brief Shared pointer alias for PersonRepository.
 *
 * Represents a shared pointer to a PersonRepository object, used for managing collections
 * of persons.
 */
typedef std::shared_ptr<PersonRepository> PersonRepositoryPtr;

/**
 * @brief Shared pointer alias for ClassRoomRepository.
 *
 * Represents a shared pointer to a ClassRoomRepository object, used for managing collections
 * of classrooms.
 */
typedef std::shared_ptr<ClassRoomRepository> ClassRoomRepositoryPtr;

/**
 * @brief Shared pointer alias for LessonRepository.
 *
 * Represents a shared pointer to a LessonRepository object, used for managing collections
 * of lessons.
 */
typedef std::shared_ptr<LessonRepository> LessonRepositoryPtr;

/**
 * @brief Shared pointer alias for PersonFilesStorage.
 *
 * Represents a shared pointer to a PersonFilesStorage object, used for file-based storage
 * and retrieval of person data.
 */
typedef std::shared_ptr<PersonFilesStorage> PersonFilesStoragePtr;

/**
 * @brief Shared pointer alias for ClassRoomFilesStorage.
 *
 * Represents a shared pointer to a ClassRoomFilesStorage object, used for file-based storage
 * and retrieval of classroom data.
 */
typedef std::shared_ptr<ClassRoomFilesStorage> ClassRoomFilesStoragePtr;

/**
 * @brief Shared pointer alias for LessonFilesStorage.
 *
 * Represents a shared pointer to a LessonFilesStorage object, used for file-based storage
 * and retrieval of lesson data.
 */
typedef std::shared_ptr<LessonFilesStorage> LessonFilesStoragePtr;

/**
 * @brief Shared pointer alias for PersonManager.
 *
 * Represents a shared pointer to a PersonManager object, used for high-level management
 * of person-related operations.
 */
typedef std::shared_ptr<PersonManager> PersonManagerPtr;

/**
 * @brief Shared pointer alias for ClassRoomManager.
 *
 * Represents a shared pointer to a ClassRoomManager object, used for high-level management
 * of classroom-related operations.
 */
typedef std::shared_ptr<ClassRoomManager> ClassRoomManagerPtr;

/**
 * @brief Shared pointer alias for LessonManager.
 *
 * Represents a shared pointer to a LessonManager object, used for high-level management
 * of lesson-related operations.
 */
typedef std::shared_ptr<LessonManager> LessonManagerPtr;

/**
 * @brief Shared pointer alias for LessonUI.
 *
 * Represents a shared pointer to a LessonUI object, used for providing a user interface
 * for lesson operations.
 */
typedef std::shared_ptr<LessonUI> LessonUIPtr;

/**
 * @brief Shared pointer alias for PersonUI.
 *
 * Represents a shared pointer to a PersonUI object, used for providing a user interface
 * for person operations.
 */
typedef std::shared_ptr<PersonUI> PersonUIPtr;

/**
 * @brief Shared pointer alias for ClassRoomUI.
 *
 * Represents a shared pointer to a ClassRoomUI object, used for providing a user interface
 * for classroom operations.
 */
typedef std::shared_ptr<ClassRoomUI> ClassRoomUIPtr;

/**
 * @brief Predicate function type for ClassRoom objects.
 *
 * Represents a function that takes a ClassRoomPtr and returns a boolean, used for filtering
 * or searching classrooms based on specific criteria.
 */
typedef std::function<bool(ClassRoomPtr)> ClassRoomPredicate;

/**
 * @brief Predicate function type for Lesson objects.
 *
 * Represents a function that takes a LessonPtr and returns a boolean, used for filtering
 * or searching lessons based on specific criteria.
 */
typedef std::function<bool(LessonPtr)> LessonPredicate;

/**
 * @brief Predicate function type for Person objects.
 *
 * Represents a function that takes a PersonPtr and returns a boolean, used for filtering
 * or searching persons based on specific criteria.
 */
typedef std::function<bool(PersonPtr)> PersonPredicate;



#endif //TYPEDEFS_H
