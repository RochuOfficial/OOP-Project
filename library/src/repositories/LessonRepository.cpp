#include "repositories/LessonRepository.h"
#include <algorithm>

#include "model/Person.h"


LessonPtr LessonRepository::getByIndex(const int &index) {
    if (index >= 0 && index < startedLessons.size()) {
        return startedLessons[index];
    }

    return nullptr;
}

LessonPtr LessonRepository::get(const LessonPtr &lesson) const {
    if (lesson == nullptr) return nullptr;

    for (const LessonPtr &lessonI : startedLessons) {
        if (lesson == lessonI) return lessonI;
    }

    for (const LessonPtr &lessonI : plannedLessons) {
        if (lesson == lessonI) return lessonI;
    }

    return nullptr;
}

std::vector<LessonPtr> LessonRepository::getStartedLessons() const {
    return startedLessons;
}

std::vector<LessonPtr> LessonRepository::getPlannedLessons() const {
    return plannedLessons;
}

std::vector<LessonPtr> LessonRepository::findAll() const {
    return findBy([](const LessonPtr &) { return true; });
}

std::vector<LessonPtr> LessonRepository::findBy(const LessonPredicate& predicate) const {
    std::vector<LessonPtr> result;

    for (auto &lesson : startedLessons) {
        if (lesson != nullptr && predicate(lesson)) result.push_back(lesson);
    }

    for (const auto &lesson : plannedLessons) {
        if (lesson != nullptr && predicate(lesson)) result.push_back(lesson);
    }

    return result;
}

LessonPtr LessonRepository::findByIndex(int index) const {
    auto result = findBy([index](const LessonPtr& lesson) {
        return lesson->getID() == index;
    });

    if (!result.empty()) {
        return result.front();
    }

    return nullptr;
}

int LessonRepository::remove(const LessonPtr &lesson) {
    if (lesson == nullptr) return 1;

    if (const auto newEndStarted = std::remove(startedLessons.begin(), startedLessons.end(), lesson); newEndStarted != startedLessons.end()) {
        startedLessons.erase(newEndStarted, startedLessons.end());
        return 0;
    }

    if (const auto newEndPlanned = std::remove(plannedLessons.begin(), plannedLessons.end(),lesson); newEndPlanned != plannedLessons.end()) {
        plannedLessons.erase(newEndPlanned, plannedLessons.end());
        return 0;
    }

    return 2;
}

int LessonRepository::removeByIndex(const int &index) {
    if (index >= 0 && index < startedLessons.size()) {
        startedLessons.erase(startedLessons.begin() + index);
        return 0;
    }

    if (index >= 0 && index < plannedLessons.size()) {
        plannedLessons.erase(plannedLessons.begin() + index);
        return 0;
    }

    return 1;
}

int LessonRepository::add(const LessonPtr &lesson, const bool now) {
    if (lesson != nullptr) {
        if (now) startedLessons.push_back(lesson);
        else {
            plannedLessons.push_back(lesson);
            lesson->getTeacher()->addFutureLesson(lesson);
        }
        return 0;
    }

    return 1;
}

int LessonRepository::size(const bool now) const {
    if (now) return static_cast<int>(startedLessons.size());
    return static_cast<int>(plannedLessons.size());
}

int LessonRepository::totalSize() const {
    return static_cast<int>(startedLessons.size() + plannedLessons.size());
}
