#include "model/Person.h"
#include <sstream>
#include <utility>


Person::Person(std::string firstName, std::string  lastName, const int id, const bool duringLesson, const int lessonId)
        : firstName(std::move(firstName)), lastName(std::move(lastName)), id(id), duringLesson(duringLesson), lessonId(lessonId)
{
}

std::string Person::getFirstName() const {
        return firstName;
}

std::string Person::getLastName() const {
        return lastName;
}

int Person::getId() const {
        return id;
}

bool Person::isDuringLesson() const {
        return duringLesson;
}

int Person::getLessonId() const {
        return lessonId;
}

void Person::setDuringLesson(const bool newDuringLesson) {
        duringLesson = newDuringLesson;
}

void Person::setLessonId(const int newLessonId) {
        if (newLessonId >= 0) {
                lessonId = newLessonId;
        }
}

void Person::setId(const int newId) {
        if (newId >= 0) {
                id = newId;
        }
}

void Person::addFutureLesson(const LessonPtr& newFutureLesson) {
        if (newFutureLesson != nullptr) {
                futureLessons.push_back(newFutureLesson);
        }
}

int Person::removeFutureLesson(const LessonPtr& futureLesson) {
        if (futureLesson != nullptr) {
                futureLessons.erase(std::remove(futureLessons.begin(), futureLessons.end(), futureLesson), futureLessons.end());
                return 0;
        }
        return 1;
}

std::vector<LessonPtr> Person::getFutureLessons() const {
        return futureLessons;
}

std::string Person::getInfo() const {
        std::stringstream ss;

        ss << "ID: " << getId();
        ss << ", First name: " << getFirstName();
        ss << ", Last Name: " << getLastName();
        ss << ", During lesson: " << isDuringLesson();

        if (isDuringLesson()) {
                ss << ", Lesson ID: " << getLessonId();
        }

        return ss.str();
}

std::string Person::getAttributes() const {
        std::stringstream ss;

        ss << getFirstName() << "," << getLastName() << "," << getId() << "," << isDuringLesson();
        ss << "," << getLessonId();

        return ss.str();
}
