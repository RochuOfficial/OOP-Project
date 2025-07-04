#include <boost/test/unit_test.hpp>
#include <boost/date_time.hpp>
#include <string>
#include "typedefs.h"
#include "model/ClassRoom.h"
#include "model/IndividualLesson.h"
#include "model/GroupLesson.h"
#include "model/ITClassRoom.h"
#include "model/Person.h"

namespace pt = boost::posix_time;
namespace bdt = boost::date_time;

struct TestSuiteLessonFixture {
    pt::ptime beginTime = bdt::not_a_date_time;
    pt::ptime endTime;
    int baseCost = 100;
    std::string subject = "IT";
    PersonPtr teacher;
    PersonPtr student;
    PersonPtr student2;
    ClassRoomTypePtr classRoomType;
    ClassRoomPtr classRoom;
    IndividualLessonPtr lesson;
    GroupLessonPtr groupLesson;

    TestSuiteLessonFixture() {
        teacher = std::make_shared<Person>("Jan", "Kowalski", 123, false, -1);
        student = std::make_shared<Person>("Kasia", "Iksinska", 312, false, -1);
        student2 = std::make_shared<Person>("Anna", "Nowak", 456, false, -1);
        classRoomType = std::make_shared<ITClassRoom>(20);
        classRoom = std::make_shared<ClassRoom>(1, true, 144, 1000.0, classRoomType);
    }
};


BOOST_FIXTURE_TEST_SUITE(TestSuiteLesson, TestSuiteLessonFixture)

BOOST_AUTO_TEST_CASE(LessonConstructorTest_Positive) {
    lesson = std::make_shared<IndividualLesson>(teacher, beginTime, baseCost, subject, classRoom, student);

    BOOST_TEST(lesson->getBaseCost() == baseCost);
    BOOST_TEST((pt::second_clock::local_time() - lesson->getBeginTime()).total_seconds() < 1);
    BOOST_TEST(lesson->getClassRoom() == classRoom);
    BOOST_TEST(lesson->getEndTime() == bdt::not_a_date_time);
    BOOST_TEST(lesson->getSubject() == subject);
    BOOST_TEST(lesson->getTeacher() == teacher);
    BOOST_TEST(lesson->getStudent() == student);
}

BOOST_AUTO_TEST_CASE(FinishLessonTest_Positive_IndividualLesson) {
    lesson = std::make_shared<IndividualLesson>(teacher, beginTime, baseCost, subject, classRoom, student);
    lesson->finishLesson();

    BOOST_TEST(lesson->getEndTime() != bdt::not_a_date_time);
    BOOST_TEST(!teacher->isDuringLesson());
    BOOST_TEST(!student->isDuringLesson());
    BOOST_TEST(classRoom->isAvailable());
    BOOST_TEST(lesson->getTotalCost() == -1);
}

BOOST_AUTO_TEST_CASE(FinishLessonTest_Negative_InvalidTime) {
    lesson = std::make_shared<IndividualLesson>(teacher, beginTime, baseCost, subject, classRoom, student);
    lesson->finishLesson();
    lesson = std::make_shared<IndividualLesson>(teacher, beginTime, baseCost, subject, classRoom, student);
    lesson->finishLesson();
    BOOST_TEST(lesson->getTotalCost() == -1);
}

BOOST_AUTO_TEST_CASE(CalculateTotalCostTest_Positive) {
    pt::ptime start = pt::second_clock::local_time();
    lesson = std::make_shared<IndividualLesson>(teacher, start, baseCost, subject, classRoom, student);
    lesson->finishLesson();
    BOOST_TEST(lesson->calculateTotalCost() == -1);
}

BOOST_AUTO_TEST_CASE(CalculateTotalCostTest_Negative_InvalidTime) {
    pt::ptime start = pt::second_clock::local_time();
    lesson = std::make_shared<IndividualLesson>(teacher, start, baseCost, subject, classRoom, student);
    BOOST_TEST(lesson->calculateTotalCost() == -1);
}

BOOST_AUTO_TEST_CASE(GroupLessonAddStudentTest_Positive) {
    groupLesson = std::make_shared<GroupLesson>(teacher, beginTime, baseCost, subject, classRoom);
    int result = groupLesson->addStudent(student);
    BOOST_TEST(result == 0);
    auto students = groupLesson->getStudents();
    BOOST_TEST(students.size() == 1);
    BOOST_TEST(students[0] == student);
    BOOST_TEST(student->isDuringLesson());
}

BOOST_AUTO_TEST_CASE(GroupLessonAddStudentTest_Negative_NullStudent) {
    groupLesson = std::make_shared<GroupLesson>(teacher, beginTime, baseCost, subject, classRoom);
    int result = groupLesson->addStudent(nullptr);
    BOOST_TEST(result != 0);
    BOOST_TEST(groupLesson->getStudents().empty());

    int result1 = groupLesson->addStudent(student);

    BOOST_TEST(result1 == 0);
    BOOST_TEST(groupLesson->getStudents().size() == 1);
}

BOOST_AUTO_TEST_CASE(GroupLessonRemoveStudentTest_Positive) {
    groupLesson = std::make_shared<GroupLesson>(teacher, beginTime, baseCost, subject, classRoom);
    groupLesson->addStudent(student);
    int result = groupLesson->removeStudent(student);
    BOOST_TEST(result == 0);
    BOOST_TEST(groupLesson->getStudents().empty());
    BOOST_TEST(!student->isDuringLesson());
}

BOOST_AUTO_TEST_CASE(GroupLessonRemoveStudentTest_Negative_NullStudent) {
    groupLesson = std::make_shared<GroupLesson>(teacher, beginTime, baseCost, subject, classRoom);
    int result = groupLesson->removeStudent(nullptr);
    BOOST_TEST(result != 0);

    int result1 = groupLesson->removeStudent(student);

    BOOST_TEST(result1 == 2);
}

BOOST_AUTO_TEST_CASE(GroupLessonFinishLessonTest_Positive) {
    groupLesson = std::make_shared<GroupLesson>(teacher, beginTime, baseCost, subject, classRoom);
    groupLesson->addStudent(student);
    groupLesson->addStudent(student2);
    groupLesson->finishLesson();
    BOOST_TEST(!student->isDuringLesson());
    BOOST_TEST(!student2->isDuringLesson());
    BOOST_TEST(!teacher->isDuringLesson());
    BOOST_TEST(classRoom->isAvailable());
}

BOOST_AUTO_TEST_CASE(LessonFinishLessonWithInvalidTimeTest) {
    pt::ptime future = pt::second_clock::local_time() + pt::hours(1);
    lesson = std::make_shared<IndividualLesson>(teacher, future, baseCost, subject, classRoom, student);
    lesson->finishLesson();

    BOOST_TEST(lesson->getEndTime().is_not_a_date_time());
}

BOOST_AUTO_TEST_SUITE_END()
