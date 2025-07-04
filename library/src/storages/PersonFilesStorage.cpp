#include "storages/PersonFilesStorage.h"
#include "typedefs.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool PersonFilesStorage::saveToFile(const PersonRepositoryPtr& personRepo) {
    const std::string fileName = "./../../database/students/Person.txt";
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }

    for (const auto& person : personRepo->findAll()) {
        outFile << person->getAttributes() << std::endl;
    }

    outFile.close();
    return true;
}

bool PersonFilesStorage::load(PersonRepositoryPtr& personRepo) {
    const std::string fileName = "./../../database/students/Person.txt";
    std::ifstream inFile(fileName);

    if (!inFile) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }

    inFile.seekg(0, std::ios::end);
    if (inFile.tellg() == 0) {
        inFile.close();
        return true;
    }
    inFile.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string token;
        std::string firstName;
        std::string lastName;
        int id;
        bool duringLesson;
        int lessonId;

        try {
            std::getline(iss, token, ','); if (token.empty()) continue; firstName = token;
            std::getline(iss, token, ','); if (token.empty()) continue; lastName = token;
            std::getline(iss, token, ','); if (token.empty()) continue; id = std::stoi(token);
            std::getline(iss, token, ','); if (token.empty()) continue; duringLesson = (token == "1");
            std::getline(iss, token, ','); if (token.empty()) continue; lessonId = std::stoi(token);

            auto person = std::make_shared<Person>(firstName, lastName, id, duringLesson, lessonId);
            personRepo->add(person);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji danych w linii: " << line << " -> " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Inny błąd podczas przetwarzania linii: " << line << " -> " << e.what() << std::endl;
        }
    }

    inFile.close();
    return true;
}

void PersonFilesStorage::saveArchive(const PersonRepositoryPtr &personRepo, const int id) {
    const std::string fileName = "./../../archive/students/Person.txt";
    std::ofstream outFile(fileName, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania pliku archiwalnego " + fileName);
    }

    const PersonPtr person = personRepo->findPersonById(id);
    if (!person) {
        throw std::logic_error("Blad, nie ma takiej osoby");
    }

    outFile << person->getAttributes() << std::endl;
    outFile.close();
}

void PersonFilesStorage::loadArchive(const PersonRepositoryPtr &personRepo, const int personalId) {
    std::vector<PersonPtr> archivePersons = getArchive();

    for (const auto& it : archivePersons) {
        if (it->getId() == personalId) {
            const auto allPersons = personRepo->findAll();

            for (const auto& person : allPersons) {
                if (person->getFirstName() == (it)->getFirstName() &&
                    person->getLastName() == (it)->getLastName()) {
                    std::cout << "W systemie jest juz identyczna osoba" << std::endl;
                    return;
                }
            }

            int newId = personalId;
            while (personRepo->findPersonById(newId)) {
                newId++;
            }

            if (newId != personalId) {
                (it)->setId(newId);
                std::cout << "Zmieniono ID przywracanej osoby na: " << newId << std::endl;
            }

            personRepo->add(it);

            archivePersons.erase(std::remove(archivePersons.begin(), archivePersons.end(), it), archivePersons.end());
            saveAllArchive(archivePersons);

            return;
        }
    }

    throw std::logic_error("Błąd podczas odczytywania archiwum");
}

void PersonFilesStorage::saveAllArchive(const std::vector<PersonPtr>& persons) {
    const std::string fileName = "./../../archive/students/Person.txt";
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania pliku archiwalnego " + fileName);
    }

    for (const auto& person : persons) {
        outFile << person->getAttributes() << std::endl;
    }

    outFile.close();
}

std::vector<PersonPtr> PersonFilesStorage::getArchive() {
    const std::string fileName = "./../../archive/students/Person.txt";
    std::ifstream inFile(fileName);

    if (!inFile) {
        throw std::runtime_error("Blad otwierania pliku archiwalnego " + fileName);
    }

    std::vector<PersonPtr> persons;
    std::string line;
    while (std::getline(inFile, line)) {
        std::istringstream iss(line);

        try {
            std::string token;
            std::string firstName;
            std::string lastName;
            int id;
            bool duringLesson;
            int lessonId;

            std::getline(iss, token, ','); if (token.empty()) continue; firstName = token;
            std::getline(iss, token, ','); if (token.empty()) continue; lastName = token;
            std::getline(iss, token, ','); if (token.empty()) continue; id = std::stoi(token);
            std::getline(iss, token, ','); if (token.empty()) continue; duringLesson = (token == "1");
            std::getline(iss, token, ','); if (token.empty()) continue; lessonId = std::stoi(token);

            auto person = std::make_shared<Person>(firstName, lastName, id, duringLesson, lessonId);
            persons.push_back(person);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji danych w archiwum: " << line << " -> " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Inny błąd podczas przetwarzania archiwum: " << line << " -> " << e.what() << std::endl;
        }
    }

    inFile.close();
    return persons;
}
