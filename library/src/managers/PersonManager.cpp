#include "managers/PersonManager.h"

#include <iostream>

#include "storages/PersonFilesStorage.h"
#include <sstream>
#include <utility>


PersonManager::PersonManager(PersonRepositoryPtr personRepo, PersonFilesStoragePtr personFilesStorage)
    : personRepo(std::move(personRepo)), personFilesStorage(std::move(personFilesStorage))
{
}

bool PersonManager::savePersons() const {
    try {
        return personFilesStorage->saveToFile(personRepo);
    } catch (std::exception &e) {
        return false;
    }
}

bool PersonManager::loadPersons() {
    try {
        return personFilesStorage->load(personRepo);
    } catch (std::runtime_error& e) {
        return false;
    }
}

void PersonManager::saveArchive(const int personalId) const {
    try {
        personFilesStorage->saveArchive(personRepo, personalId);
    } catch (std::runtime_error& e) {
        std::cerr << "Blad archiwum: " << e.what() << std::endl;
    }
}

void PersonManager::loadArchive(const int personalId) const {
    try {
        personFilesStorage->loadArchive(personRepo, personalId);
    } catch (std::runtime_error& e) {
        std::cerr << "Blad archiwum: " << e.what() << std::endl;
    }
}

std::vector<PersonPtr> PersonManager::getArchive() const {
    try {
        return personFilesStorage->getArchive();
    } catch (std::runtime_error& e) {
        std::cerr << "Blad archiwum: " << e.what() << std::endl;
        return {};
    }
}

PersonPtr PersonManager::addPerson(const std::string& firstName, const std::string& lastName, int id, bool duringLesson,
                                   int lessonId) const {
    if (const PersonPtr person = personRepo->findPersonById(id); person != nullptr) return person;

    const auto newPerson = std::make_shared<Person>(firstName, lastName, id, duringLesson, lessonId);
    personRepo->add(newPerson);

    return newPerson;
}

void PersonManager::removePerson(const int id) const {
    if (const PersonPtr person = personRepo->findPersonById(id); person != nullptr) {
        saveArchive(id);
        personRepo->remove(person);
    }
}

PersonPtr PersonManager::getPerson(const int id) const {
    return personRepo->findPersonById(id);
}

std::string PersonManager::report() const {
    std::stringstream ss;

    for (auto& person : personRepo->findAll()) {
        if (person != nullptr) {
            ss << person->getInfo() << std::endl;
        }
    }

    return ss.str();
}

std::vector<PersonPtr> PersonManager::findAllPersons() const {
    return findPersons([](const PersonPtr&){ return true;});
}

std::vector<PersonPtr> PersonManager::findPersons(const PersonPredicate& predicate) const {
    return personRepo->findBy([predicate](const PersonPtr& person) {
        return predicate(person);
    });
}
