#include "managers/LessonManager.h"
#include "storages/LessonFilesStorage.h"
#include "repositories/LessonRepository.h"
#include "repositories/PersonRepository.h"
#include "repositories/ClassRoomRepository.h"
#include "model/ClassRoom.h"
#include "model/IndividualLesson.h"
#include "model/Lesson.h"
#include "model/Person.h"
#include "typedefs.h"
#include <sstream>
#include <utility>


LessonManager::LessonManager(LessonRepositoryPtr  lessonRepo, LessonFilesStoragePtr  lessonFilesStorage, PersonRepositoryPtr  personRepo,
                  ClassRoomRepositoryPtr  classRoomRepo)
    : lessonRepo(std::move(lessonRepo)), lessonFilesStorage(std::move(lessonFilesStorage)), personRepo(std::move(personRepo)), classRoomRepo(std::move(classRoomRepo))
{
}

bool LessonManager::save() const {
    try {
        return lessonFilesStorage->saveToFile(lessonRepo);
    } catch (std::exception& e) {
        return false;
    }
}

bool LessonManager::load() {
    bool flag=true;
    try {
        lessonFilesStorage->load(lessonRepo);
    } catch (std::exception& e) {
        flag = false;
    }

    return flag;
}

LessonRepositoryPtr LessonManager::getLessonRepo() const {
    return lessonRepo;
}

int LessonManager::removeLesson(const int &id) const {
    if (const LessonPtr lesson = lessonRepo->findByIndex(id); lesson != nullptr) {
        try {
            saveArchive(id);
        } catch (const std::exception& e) {
            std::cerr << "Blad archiwum: " << e.what() << std::endl;
        }
        return lessonRepo->remove(lesson);
    }

    return 1;
}

LessonPtr LessonManager::addGroupLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom, const bool now) const {
    auto newLesson = std::make_shared<GroupLesson>(teacher, beginTime, endTime, baseCost, subject, classRoom);

    lessonRepo->add(newLesson, now);

    if (!now) {
        for (const auto& person : newLesson->getStudents()) {
            person->addFutureLesson(newLesson);
        }
    }

    return newLesson;
}

LessonPtr LessonManager::addIndividualLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, int baseCost, const std::string &subject, const ClassRoomPtr &classRoom, const PersonPtr &individualPerson, const bool now) const {
    auto newLesson = std::make_shared<IndividualLesson>(teacher, beginTime, endTime, baseCost, subject, classRoom, individualPerson);

    lessonRepo->add(newLesson, now);
    if (!now)
        newLesson->getStudent()->addFutureLesson(newLesson);

    return newLesson;
}

int LessonManager::addStudentToGroupLesson(const int &id, const PersonPtr& person) const {
    const auto lesson = lessonRepo->findByIndex(id);
    if (lesson == nullptr) return 3;
    if (person == nullptr) return 4;

    const auto groupLesson = std::dynamic_pointer_cast<GroupLesson>(lesson);

    person->addFutureLesson(groupLesson);

    return groupLesson->addStudent(person);
}

int LessonManager::removeStudentFromGroupLesson(const int &id, const PersonPtr &person) const {
    const LessonPtr lesson = lessonRepo->getByIndex(id);

    if (lesson == nullptr) return 3;
    if (person == nullptr) return 4;
    if (person->getLessonId() != id) return 5;

    const auto groupLesson = std::dynamic_pointer_cast<GroupLesson>(lesson);

    return groupLesson->removeStudent(person);
}

LessonPtr LessonManager::getLesson(const int &id) const {
    return lessonRepo->findByIndex(id);
}

std::string LessonManager::report() const {
    std::stringstream ss;
    int counter = 1;

    for (const LessonPtr &lessonI : lessonRepo->findAll()) {
        ss << counter << ". " << lessonI->getInfo() << std::endl;
        counter++;
    }

    return ss.str();
}

bool LessonManager::startLesson(const int &id) const {
    const LessonPtr lesson = lessonRepo->findByIndex(id);
    if (!lesson) {
        std::cerr << "Nie znaleziono lekcji o ID " << id << std::endl;
        return false;
    }
    lesson->getClassRoom()->setAvailable(false);

    if (std::dynamic_pointer_cast<IndividualLesson>(lesson)) {
        const auto  individual = std::dynamic_pointer_cast<IndividualLesson>(lesson);
        individual->startLesson(true);
        individual->getStudent()->removeFutureLesson(lesson);
        individual->getStudent()->setDuringLesson(true);
        individual->getStudent()->setLessonId(lesson->getID());
        individual->getTeacher()->setDuringLesson(true);
        individual->getTeacher()->setLessonId(lesson->getID());
        return true;
    }

    if (std::dynamic_pointer_cast<GroupLesson>(lesson)) {
        const auto  groupLesson = std::dynamic_pointer_cast<GroupLesson>(lesson);
        groupLesson->startLesson(true);
        std::vector students = groupLesson->getStudents();
        lesson->getTeacher()->removeFutureLesson(lesson);
        lesson->getTeacher()->setDuringLesson(true);
        lesson->getTeacher()->setLessonId(lesson->getID());
        for (auto& student : students) {
            student->removeFutureLesson(lesson);
            student->setDuringLesson(true);
            student->setLessonId(lesson->getID());
        }
        return true;
    }
    return false;
}

bool LessonManager::finishLesson(const int &id) const {
    const auto lesson = lessonRepo->findByIndex(id);
    if (!lesson) {
        std::cerr << "Nie znaleziono lekcji o ID " << id << std::endl;
        return false;
    }

    for (const auto& person : personRepo->findAll()) {
        if (person->getLessonId() == id) {
            person->setDuringLesson(false);
            person->setLessonId(-1);
        }
    }

    const int classRoomId = lesson->getClassRoom()->getNumber();

    if (const auto classRoom = classRoomRepo->findClassRoomByNumber(classRoomId); classRoom) {
        classRoom->setAvailable(true);
    } else {
        std::cerr << "Nie znaleziono sali o ID " << classRoomId << std::endl;
    }

    lesson->finishLesson();

    if (removeLesson(id) == 0) {
        return true;
    }
    return false;
}


std::vector<LessonPtr> LessonManager::findLessons(const LessonPredicate& predicate) const {
    return lessonRepo->findBy([predicate](const LessonPtr &lesson) {
        return predicate(lesson);
    });
}

std::vector<LessonPtr> LessonManager::findAllLessons() const {
    return findLessons([](const LessonPtr &) { return true; });
}

std::vector<LessonPtr> LessonManager::findStartedLessons() const {
    return lessonRepo->getStartedLessons();
}

std::vector<LessonPtr> LessonManager::findPlannedLessons() const {
    return lessonRepo->getPlannedLessons();
}

void LessonManager::saveArchive(const int personalId) const {
    try {
        lessonFilesStorage->saveArchive(lessonRepo, personalId);
    } catch (const std::exception &e) {
        std::cerr << "Blad archiwum: " << e.what() << std::endl;
    }
}

void LessonManager::showArchive() const {
    try {
        lessonFilesStorage->showArchive();
    } catch (const std::exception &e) {
        std::cerr << "Blad archiwum: " << e.what() << std::endl;
    }
}
