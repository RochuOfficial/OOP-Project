#include "repositories/PersonRepository.h"
#include <algorithm>
#include <fstream>


void PersonRepository::remove(const PersonPtr& person) {
    if (person != nullptr) {
        persons.erase(std::remove(persons.begin(), persons.end(), person), persons.end());
    }
}

void PersonRepository::add(const PersonPtr& person) {
    if (person != nullptr) {
        persons.push_back(person);
    }
}

int PersonRepository::size() const {
    return static_cast<int>(persons.size());
}

PersonPtr PersonRepository::findPersonById(int id) const {
    auto result = findBy([id](const PersonPtr& person) {
        return person->getId() == id;
    });

    if (!result.empty()) {
        return result.front();
    }

    return nullptr;
}

std::vector<PersonPtr> PersonRepository::findBy(const PersonPredicate& predicate) const {
    std::vector<PersonPtr> result;

    for (auto& person : persons) {
        if (predicate(person) && person != nullptr) {
            result.push_back(person);
        }
    }

    return result;
}

std::vector<PersonPtr> PersonRepository::findAll() const {
    return findBy([](const PersonPtr&){ return true;});
}
