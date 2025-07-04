#include "model/IndividualLesson.h"
#include "model/Person.h"


IndividualLesson::IndividualLesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, const int baseCost,
                                   const std::string &subject, const ClassRoomPtr &classRoom, const PersonPtr &student)
        : Lesson(teacher, beginTime, endTime, baseCost, subject, classRoom), student(student) {
}

IndividualLesson::~IndividualLesson() = default;

PersonPtr IndividualLesson::getStudent() const {
    return student;
}

PersonPtr IndividualLesson::getTeacher() const {
    return Lesson::getTeacher();
}

pt::ptime IndividualLesson::getBeginTime() const {
    return Lesson::getBeginTime();
}

pt::ptime IndividualLesson::getEndTime() const {
    return Lesson::getEndTime();
}

int IndividualLesson::getBaseCost() const {
    return Lesson::getBaseCost();
}

std::string IndividualLesson::getSubject() const {
    return Lesson::getSubject();
}

ClassRoomPtr IndividualLesson::getClassRoom() const {
    return Lesson::getClassRoom();
}

int IndividualLesson::getID() const {
    return Lesson::getID();
}

long IndividualLesson::getTotalCost() const {
    return Lesson::getTotalCost();
}

bool IndividualLesson::isStarted() const {
    return Lesson::isStarted();
}

void IndividualLesson::startLesson(const bool start) {
    Lesson::startLesson(start);
}

void IndividualLesson::finishLesson() {
    Lesson::finishLesson();

    student->setDuringLesson(false);
    student->setLessonId(-1);
}

long IndividualLesson::calculateTotalCost() const {
    return Lesson::calculateTotalCost();
}

std::string IndividualLesson::getInfo() const {
    std::stringstream ss;

    ss << Lesson::getInfo();
    ss << "\tStudent: " << student->getInfo() << std::endl;

    return ss.str();
}

std::string IndividualLesson::getAttributes() const {
    std::ostringstream ss;

    ss << "INDIVIDUAL," << Lesson::getAttributes() << ","
        << student->getAttributes();

    return ss.str();
}
