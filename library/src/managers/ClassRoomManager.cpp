#include "managers/ClassRoomManager.h"
#include "storages/ClassRoomFilesStorage.h"
#include <iostream>
#include <sstream>
#include <utility>


ClassRoomManager::ClassRoomManager(ClassRoomRepositoryPtr classRoomRepo, ClassRoomFilesStoragePtr classRoomFilesStorage)
        : classRoomRepo(std::move(classRoomRepo)), classRoomFilesStorage(std::move(classRoomFilesStorage))
{
}

bool ClassRoomManager::saveClassRooms() const {
    try {
        return classRoomFilesStorage->saveToFile(classRoomRepo);
    } catch (std::exception &e) {
        return false;
    }
}

bool ClassRoomManager::loadClassRooms() {
    try {
        return classRoomFilesStorage->load(classRoomRepo);
    } catch (std::runtime_error& e) {
        return false;
    }
}

void ClassRoomManager::saveArchive(const int classRoomNumber) const {
    try {
        classRoomFilesStorage->saveArchive(classRoomRepo, classRoomNumber);
    } catch (std::runtime_error& e) {
        std::cerr << "Blad zapisu do archiwum: " << e.what() << std::endl;
    }
}

void ClassRoomManager::loadArchive(const int classRoomNumber) const {
    try {
        classRoomFilesStorage->loadArchive(classRoomRepo, classRoomNumber);
    } catch (std::runtime_error& e) {
        std::cerr << "Blad odczytywania archiwum: " << e.what() << std::endl;
    }
}

std::vector<ClassRoomPtr> ClassRoomManager::getArchive() const {
    try {
        return classRoomFilesStorage->getArchive();
    } catch (std::runtime_error& e) {
        std::cerr << "Blad ladowania archiwum: " << e.what() << std::endl;
        return {};
    }
}

ClassRoomPtr ClassRoomManager::getClassRoom(const int number) const {
    return classRoomRepo->findClassRoomByNumber(number);
}

ClassRoomPtr ClassRoomManager::addClassRoom(int number, bool available, int seatsNumber, double rentCost,
    const ClassRoomTypePtr& classRoomType) const {

    if (const ClassRoomPtr classRoom = classRoomRepo->findClassRoomByNumber(number); classRoom != nullptr) {
        return classRoom;
    }

    auto newClassRoom = std::make_shared<ClassRoom>(number, available, seatsNumber, rentCost, classRoomType);
    classRoomRepo->add(newClassRoom);

    return newClassRoom;
}

void ClassRoomManager::removeClassRoom(const int number) const {
    if (const ClassRoomPtr classRoom = classRoomRepo->findClassRoomByNumber(number); classRoom != nullptr) {
        saveArchive(number);
        classRoomRepo->remove(classRoom);
    }
}

std::string ClassRoomManager::report() const {
    std::stringstream ss;

    for (auto& room : classRoomRepo->findAll()) {
        if (room != nullptr) {
            ss << room->getNumber() << ". " << room->getInfo() << std::endl;
        }
    }

    return ss.str();
}

std::vector<ClassRoomPtr> ClassRoomManager::findClassRooms(const ClassRoomPredicate& predicate) const {
    return classRoomRepo->findBy([predicate](const ClassRoomPtr& classRoom) {
        return predicate(classRoom);
    });
}

std::vector<ClassRoomPtr> ClassRoomManager::findAllClassRooms() const {
    return findClassRooms([](const ClassRoomPtr&) { return true;});
}
