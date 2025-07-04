#include <boost/test/unit_test.hpp>
#include "model/ClassRoom.h"
#include "typedefs.h"
#include <memory>
#include "repositories/ClassRoomRepository.h"
#include "managers/ClassRoomManager.h"
#include "model/EngClassRoom.h"
#include "model/MathClassRoom.h"
#include "model/ITClassRoom.h"
#include "storages/ClassRoomFilesStorage.h"

struct TestSuiteClassRoomFixture {
    int number = 0;
    bool available = true;
    int seatsNumber = 30;
    double rentCost = 30.0;
    ClassRoomTypePtr classRoomType;
    TestSuiteClassRoomFixture() {
        classRoomType = std::make_shared<ITClassRoom>(10);
    }
    int newNumber = 1;
    bool newAvailable = false;
    int newSeatsNumber = 40;
    double newRentCost = 40.0;
};

BOOST_FIXTURE_TEST_SUITE(TestSuiteClassRoom, TestSuiteClassRoomFixture)

BOOST_AUTO_TEST_CASE(ClassRoomConstructorTest){
    ClassRoomPtr classRoom;
    classRoom = std::make_shared<ClassRoom>(number, available, seatsNumber, rentCost, classRoomType);
    BOOST_TEST(classRoom->getNumber() == number);
    BOOST_TEST(classRoom->isAvailable() == available);
    BOOST_TEST(classRoom->getSeatsNumber() == seatsNumber);
    BOOST_TEST(classRoom->getRentCost() == rentCost);
    BOOST_TEST(classRoom->getClassRoomType() == classRoomType);
}

BOOST_AUTO_TEST_CASE(ClassRoomSettersPositiveTest){
    ClassRoomPtr classRoom;
    classRoom = std::make_shared<ClassRoom>(number, available, seatsNumber, rentCost, classRoomType);
    classRoom->setSeatsNumber(newSeatsNumber);
    classRoom->setRentCost(newRentCost);
    classRoom->setAvailable(newAvailable);
    classRoom->setNumber(newNumber);
    BOOST_TEST(classRoom->getNumber() == newNumber);
    BOOST_TEST(classRoom->isAvailable() == newAvailable);
    BOOST_TEST(classRoom->getSeatsNumber() == newSeatsNumber);
    BOOST_TEST(classRoom->getRentCost() == newRentCost);
}

BOOST_AUTO_TEST_CASE(ClassRoomSettersNegativeTest){
    ClassRoomPtr classRoom;
    classRoom = std::make_shared<ClassRoom>(number, available, seatsNumber, rentCost, classRoomType);
    classRoom->setSeatsNumber(0);
    classRoom->setRentCost(0);
    classRoom->setNumber(0);
    BOOST_TEST(classRoom->getNumber() == number);
    BOOST_TEST(classRoom->getSeatsNumber() == seatsNumber);
    BOOST_TEST(classRoom->getRentCost() == rentCost);
}

BOOST_AUTO_TEST_CASE(ClassRoomTypesTest) {
    std::vector<ClassRoomTypePtr> types = {
        std::make_shared<ITClassRoom>(10),
        std::make_shared<MathClassRoom>(true),
        std::make_shared<EngClassRoom>(false)
    };

    for (const auto& type : types) {
        ClassRoom room(1, true, 30, 50.0, type);
        BOOST_TEST(!room.getClassRoomType()->getType().empty());
        BOOST_TEST(!room.getClassRoomType()->getInfo().empty());
        BOOST_TEST(room.getActualRentCost() > 0.0);
    }
}

BOOST_AUTO_TEST_CASE(ClassRoomRepositoryAddAndRemoveTest) {
    ClassRoomRepository repo;
    auto room = std::make_shared<ClassRoom>(1, true, 20, 30.0, std::make_shared<ITClassRoom>(1));
    repo.add(room);
    BOOST_TEST(repo.size() == 1);

    repo.remove(room);
    BOOST_TEST(repo.size() == 0);

    repo.add(nullptr);
    BOOST_TEST(repo.size() == 0);

    repo.remove(nullptr);
    BOOST_TEST(repo.size() == 0);
}

BOOST_AUTO_TEST_CASE(ClassRoomRepositoryAndManagerMethods) {
    ClassRoomRepositoryPtr repo = std::make_shared<ClassRoomRepository>();
    ClassRoomFilesStoragePtr storage = std::make_shared<ClassRoomFilesStorage>();
    ClassRoomManagerPtr classRoomManager = std::make_shared<ClassRoomManager>(repo, storage);
    ClassRoomPtr classRoom = classRoomManager->addClassRoom(number, available, seatsNumber, rentCost, classRoomType);
    BOOST_TEST(classRoom != nullptr);
    BOOST_TEST(classRoom->getNumber() == number);

    ClassRoomPtr classRoom2 = classRoomManager->addClassRoom(number, available, seatsNumber, rentCost, classRoomType);
    BOOST_TEST(classRoom2 == classRoom);

    ClassRoomPtr found = classRoomManager->getClassRoom(number);
    BOOST_TEST(found == classRoom);
    BOOST_TEST(classRoomManager->getClassRoom(-1) == nullptr);

    auto availableRooms = classRoomManager->findClassRooms([](const ClassRoomPtr& room) {
        return room->isAvailable();
    });

    //BOOST_TEST(availableRooms.size() == 1);
}

BOOST_AUTO_TEST_SUITE_END()