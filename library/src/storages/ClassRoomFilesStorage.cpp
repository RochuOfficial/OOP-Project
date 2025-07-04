#include "storages/ClassRoomFilesStorage.h"
#include "model/ITClassRoom.h"
#include "model/EngClassRoom.h"
#include "model/MathClassRoom.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>


bool ClassRoomFilesStorage::saveToFile(const ClassRoomRepositoryPtr &classRoomRepo) {
    const std::string fileName = "./../../database/classrooms/Classroom.txt";
    std::ofstream outputFile(fileName);

    if (!outputFile) {
        throw std::runtime_error("Blad tworzenia pliku " + fileName);
    }

    for (const auto& room : classRoomRepo->findAll()) {
        outputFile << room->getAttributes() << std::endl;
    }
    outputFile.close();
    return true;
}

bool ClassRoomFilesStorage::load(ClassRoomRepositoryPtr &classRoomRepo) {
    const std::string fileName = "./../../database/classrooms/Classroom.txt";
    std::ifstream inputFile(fileName);

    if (!inputFile) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }

    inputFile.seekg(0, std::ios::end);
    if (inputFile.tellg() == 0) {
        inputFile.close();
        return true;
    }
    inputFile.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);

        try {
            std::string token;

            std::getline(iss, token, ',');
            if (token.empty()) continue;
            int number = std::stoi(token);

            std::getline(iss, token, ',');
            bool available = (token == "1");

            std::getline(iss, token, ',');
            int seatsNumber = std::stoi(token);

            std::getline(iss, token, ',');
            double rentCost = std::stod(token);

            std::getline(iss, token, ',');
            std::string type = token;

            std::getline(iss, token, ',');
            int extraInt = std::stoi(token);

            ClassRoomTypePtr classRoomType;
            if (type == "IT") {
                classRoomType = std::make_shared<ITClassRoom>(extraInt);
            } else if (type == "MATH") {
                classRoomType = std::make_shared<MathClassRoom>(extraInt == 1);
            } else if (type == "ENG") {
                classRoomType = std::make_shared<EngClassRoom>(extraInt == 1);
            } else {
                continue;
            }

            auto classRoom = std::make_shared<ClassRoom>(
                number, available, seatsNumber, rentCost, classRoomType);
            classRoomRepo->add(classRoom);

        } catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji: " << e.what() << " w linii: " << line << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Inny błąd: " << e.what() << std::endl;
        }
    }

    inputFile.close();
    return true;
}

void ClassRoomFilesStorage::saveArchive(const ClassRoomRepositoryPtr &classRoomRepo, const int number) {
    const std::string fileName = "./../../archive/classrooms/Classroom.txt";
    std::ofstream outFile(fileName, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania archiwalnego pliku " + fileName);
    }

    const auto classRoom = classRoomRepo->findClassRoomByNumber(number);
    if (!classRoom) {
        throw std::logic_error("Blad, nie ma takiej sali");
    }

    outFile << classRoom->getAttributes() << std::endl;
    outFile.close();
}

void ClassRoomFilesStorage::loadArchive(const ClassRoomRepositoryPtr &classRoomRepo, const int classRoomNumber) {
    std::vector<ClassRoomPtr> archiveClassRooms = getArchive();

    for (const auto& it : archiveClassRooms) {
        if (it->getNumber() == classRoomNumber) {
            const auto allClassRooms = classRoomRepo->findAll();
            for (const auto& room : allClassRooms) {
                if (room->getSeatsNumber() == (it)->getSeatsNumber() &&
                    room->getRentCost() == (it)->getRentCost() &&
                    room->getClassRoomType()->getType() == (it)->getClassRoomType()->getType()) {
                    std::cout << "W systemie jest juz identyczna sala" << std::endl;
                    return;
                    }
            }

            int newNumber = classRoomNumber;
            while (classRoomRepo->findClassRoomByNumber(newNumber)) {
                newNumber++;
            }
            if (newNumber != classRoomNumber) {
                (it)->setNumber(newNumber);
                std::cout << "Zmieniono numer przywracanej sali na: " << newNumber << std::endl;
            }

            classRoomRepo->add(it);

            archiveClassRooms.erase(std::remove(archiveClassRooms.begin(), archiveClassRooms.end(), it), archiveClassRooms.end());
            saveAllArchive(archiveClassRooms);

            return;
        }
    }

    throw std::logic_error("Błąd podczas odczytywania archiwum");
}

void ClassRoomFilesStorage::saveAllArchive(const std::vector<ClassRoomPtr> &classrooms) {
    const std::string fileName = "./../../archive/classrooms/Classroom.txt";
    std::ofstream outFile(fileName);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania archiwalnego pliku " + fileName);
    }

    for (const auto& room : classrooms) {
        outFile << room->getAttributes() << std::endl;
    }

    outFile.close();
}

std::vector<ClassRoomPtr> ClassRoomFilesStorage::getArchive() {
    const std::string fileName = "./../../archive/classrooms/Classroom.txt";
    std::ifstream inFile(fileName);

    if (!inFile) {
        throw std::runtime_error("Blad otwierania archiwalnego pliku " + fileName);
    }

    std::vector<ClassRoomPtr> classRooms;
    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);

        try {
            std::string token;

            std::getline(iss, token, ',');
            if (token.empty()) continue;
            int number = std::stoi(token);

            std::getline(iss, token, ',');
            bool available = (token == "1");

            std::getline(iss, token, ',');
            int seatsNumber = std::stoi(token);

            std::getline(iss, token, ',');
            double rentCost = std::stod(token);

            std::getline(iss, token, ',');
            std::string type = token;

            std::getline(iss, token, ',');
            int extraInt = std::stoi(token);

            ClassRoomTypePtr classRoomType;
            if (type == "IT") {
                classRoomType = std::make_shared<ITClassRoom>(extraInt);
            } else if (type == "MATH") {
                classRoomType = std::make_shared<MathClassRoom>(extraInt == 1);
            } else if (type == "ENG") {
                classRoomType = std::make_shared<EngClassRoom>(extraInt == 1);
            } else {
                continue;
            }

            auto classRoom = std::make_shared<ClassRoom>(
                number, available, seatsNumber, rentCost, classRoomType);
            classRooms.push_back(classRoom);

        } catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji: " << e.what() << " w linii: " << line << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Inny błąd: " << e.what() << std::endl;
        }
    }
    inFile.close();
    return classRooms;
}
