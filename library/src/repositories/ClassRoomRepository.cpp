#include "repositories/ClassRoomRepository.h"
#include <algorithm>
#include <fstream>


ClassRoomPtr ClassRoomRepository::findClassRoomByNumber(int number) const {
    auto results = findBy([number](const ClassRoomPtr& classRoom){
    return classRoom->getNumber() == number;
  });

    if (!results.empty()){
        return results.front();
    }

    return nullptr;
}

void ClassRoomRepository::add(const ClassRoomPtr& classRoom) {
    if (classRoom != nullptr) {
        rooms.push_back(classRoom);
    }
}

void ClassRoomRepository::remove(const ClassRoomPtr& classRoom) {
    if (classRoom != nullptr) {
        rooms.erase(std::remove(rooms.begin(), rooms.end(), classRoom));
    }
}

int ClassRoomRepository::size() const {
    return static_cast<int>(rooms.size());
}

std::vector<ClassRoomPtr> ClassRoomRepository::findAll() const {
    return findBy([](const ClassRoomPtr&){ return true; });
}

std::vector<ClassRoomPtr> ClassRoomRepository::findBy(const ClassRoomPredicate& predicate) const {
    std::vector<ClassRoomPtr> result;

    for (auto& room : rooms) {
        if (room != nullptr && predicate(room)) {
            result.push_back(room);
        }
    }
    return result;
}
