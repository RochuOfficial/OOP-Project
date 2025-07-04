#include "model/Lesson.h"
#include "model/ClassRoom.h"
#include "model/Person.h"
#include <sstream>
#include <cmath>
#include <utility>


int Lesson::counter = 0;

Lesson::Lesson(const PersonPtr &teacher, const pt::ptime &beginTime, const pt::ptime &endTime, const int baseCost, std::string subject, const ClassRoomPtr &classRoom)
        : teacher(teacher),
          startTime(beginTime),
          endTime(endTime),
          baseCost(baseCost),
          subject(std::move(subject)),
          classRoom(classRoom),
          totalCost(-1) {
    id = ++counter;
}

Lesson::~Lesson() = default;

bool Lesson::isStarted() const {
    return started;
}

void Lesson::startLesson(const bool start) {
    started = start;
}

void Lesson::finishLesson() {
    endTime = pt::second_clock::local_time();
    if (startTime > endTime) {
        endTime = bdt::not_a_date_time;
        return;
    }

    teacher->setDuringLesson(false);
    teacher->setLessonId(-1);
    classRoom->setAvailable(true);
    totalCost = calculateTotalCost();
}

PersonPtr Lesson::getTeacher() const {
    return teacher;
}

pt::ptime Lesson::getBeginTime() const {
    return startTime;
}

pt::ptime Lesson::getEndTime() const {
    return endTime;
}

int Lesson::getBaseCost() const {
    return baseCost;
}

std::string Lesson::getSubject() const {
    return subject;
}

ClassRoomPtr Lesson::getClassRoom() const {
    return classRoom;
}

int Lesson::getID() const {
    return id;
}

long Lesson::getTotalCost() const {
    return totalCost;
}

long Lesson::calculateTotalCost() const {
    if (endTime.is_not_a_date_time() || startTime >= endTime) return -1;

    const pt::time_period period(startTime, endTime);

    if (period.length().total_seconds() < 60) return 0;

    const long minutes = std::ceil(period.length().total_seconds() / 60);

    return minutes * static_cast<long>(baseCost) + static_cast<long>(classRoom->getActualRentCost());
}

std::string Lesson::getInfo() const {
    std::stringstream ss;

    ss << "Lekcja nr: " << getID() << std::endl;
    ss << ", godzina rozpoczecia: " << getBeginTime() << ", godzina zakonczenia: " << getEndTime() <<  std::endl;
    ss << "\tSala: " << classRoom->getInfo() << std::endl;
    ss << "\tNauczyciel: " << teacher->getInfo() << std::endl;

    return ss.str();
}

std::string Lesson::getAttributes() const {
    std::ostringstream ss;

    ss << getID() << ","
        << getBaseCost() << ","
        << getSubject() << ","
        << boost::posix_time::to_simple_string(startTime) << ","
        << boost::posix_time::to_simple_string(endTime) << ","
        << classRoom->getAttributes() << ","
        << teacher->getAttributes();

    return ss.str();
}
