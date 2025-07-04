#include "model/Person.h"
#include "model/GroupLesson.h"
#include <sstream>
#include <algorithm>


GroupLesson::GroupLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, const int baseCost, const std::string &subject, const ClassRoomPtr &classRoom)
    : Lesson(teacher, beginTime, endTime, baseCost, subject, classRoom) {

}

GroupLesson::~GroupLesson() = default;

std::vector<PersonPtr> GroupLesson::getStudents() const {
    return students;
}

PersonPtr GroupLesson::getTeacher() const {
    return Lesson::getTeacher();
}

pt::ptime GroupLesson::getBeginTime() const {
    return Lesson::getBeginTime();
}

pt::ptime GroupLesson::getEndTime() const {
    return Lesson::getEndTime();
}

int GroupLesson::getBaseCost() const {
    return Lesson::getBaseCost();
}

std::string GroupLesson::getSubject() const {
    return Lesson::getSubject();
}

ClassRoomPtr GroupLesson::getClassRoom() const {
    return Lesson::getClassRoom();
}

int GroupLesson::getID() const {
    return Lesson::getID();
}

long GroupLesson::getTotalCost() const {
    return Lesson::getTotalCost();
}

bool GroupLesson::isStarted() const {
    return Lesson::isStarted();
}

void GroupLesson::startLesson(const bool start) {
    Lesson::startLesson(start);
}

int GroupLesson::addStudent(const PersonPtr &student) {
    if (student == nullptr) return 1;

    students.push_back(student);

    return 0;
}

int GroupLesson::removeStudent(const PersonPtr &student) {
    if (student == nullptr) return 1;
    if (!student->isDuringLesson()) return 2;

    students.erase(std::remove(students.begin(), students.end(), student), students.end());
    student->setDuringLesson(false);

    return 0;
}

void GroupLesson::finishLesson() {
    Lesson::finishLesson();

    for (const PersonPtr &student : students) {
        student->setDuringLesson(false);
        student->setLessonId(-1);
    }
}

long GroupLesson::calculateTotalCost() const {
    return Lesson::calculateTotalCost();
}

std::string GroupLesson::getInfo() const {
    std::stringstream ss;

    ss << Lesson::getInfo();
    ss << "\tStudenci:" << std::endl;
    for (const PersonPtr &student : students) {
        ss << "\t\t" << student->getInfo() << std::endl;
    }

    return ss.str();
}

std::string GroupLesson::getAttributes() const {
    std::ostringstream oss;

    oss << "GROUP," << Lesson::getAttributes();

    if (!students.empty()) {
        for (const PersonPtr &student : students) {
            oss << ",";
            oss << student->getAttributes();
        }
    }

    return oss.str();
}
