#include "typedefs.h"
#include "storages/LessonFilesStorage.h"
#include "model/ClassRoom.h"
#include "model/Person.h"
#include "model/ITClassRoom.h"
#include "model/EngClassRoom.h"
#include "model/MathClassRoom.h"
#include "model/IndividualLesson.h"
#include "model/GroupLesson.h"
#include "repositories/LessonRepository.h"
#include <fstream>
#include <stdexcept>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace pt = boost::posix_time;


LessonFilesStorage::LessonFilesStorage() = default;

LessonFilesStorage::~LessonFilesStorage() = default;

bool LessonFilesStorage::saveToFile(const LessonRepositoryPtr& repository) {
    const std::string fileName = "./../../database/lessons/Lesson.txt";
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }
    for (const auto& lesson : repository->findAll()) {
        outFile << lesson->getAttributes() << std::endl;
    }
    outFile.close();
    return true;
}

bool LessonFilesStorage::load(LessonRepositoryPtr& repository) {
    const std::string fileName = "./../../database/lessons/Lesson.txt";
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
        std::istringstream iss(line);
        std::string token;

        std::string lessonType;
        std::getline(iss, lessonType, ',');

        try {
            std::string subject;
            pt::ptime beginTime;
            pt::ptime endTime;
            int lessonId;
            int baseCost;
            std::string teacherFirstName;
            std::string teacherLastName;
            int teacherId;
            bool teacherDuringLesson;
            int classNumber;
            int seatsNumber;
            double classRentCost;
            bool available;
            std::string classType;
            int classEquipment;

            std::getline(iss, token, ','); lessonId = atoi(token.c_str());
            std::getline(iss, token, ','); baseCost = atoi(token.c_str());
            std::getline(iss, token, ','); subject = token;
            std::getline(iss, token, ','); beginTime = pt::time_from_string(token);
            std::getline(iss, token, ','); endTime = pt::time_from_string(token);
            std::getline(iss, token, ','); classNumber = atoi(token.c_str());
            std::getline(iss, token, ','); available = atoi(token.c_str());
            std::getline(iss, token, ','); seatsNumber = atoi(token.c_str());
            std::getline(iss, token, ','); classRentCost = std::stod(token);
            std::getline(iss, token, ','); classType = token;
            std::getline(iss, token, ','); classEquipment = std::stoi(token);
            std::getline(iss, token, ','); teacherFirstName = token;
            std::getline(iss, token, ','); teacherLastName = token;
            std::getline(iss, token, ','); teacherId = atoi(token.c_str());
            std::getline(iss, token, ','); teacherDuringLesson = atoi(token.c_str());
            std::getline(iss, token, ','); lessonId = atoi(token.c_str());

            auto teacher = std::make_shared<Person>(teacherFirstName, teacherLastName, teacherId, teacherDuringLesson, lessonId);
            ClassRoomTypePtr classRoomType;
            if (classType == "IT") {
                classRoomType = std::make_shared<ITClassRoom>(classEquipment);
            } else if (classType == "MATH") {
                classRoomType = std::make_shared<MathClassRoom>(classEquipment == 1);
            } else if (classType == "ENG") {
                classRoomType = std::make_shared<EngClassRoom>(classEquipment == 1);
            }

            auto classRoom = std::make_shared<ClassRoom>(classNumber, available, seatsNumber, classRentCost, classRoomType);

            if (lessonType == "INDIVIDUAL") {
                std::string studentFirstName, studentLastName;
                int studentId;
                bool studentDuringLesson;

                std::getline(iss, studentFirstName, ',');
                std::getline(iss, studentLastName, ',');
                std::getline(iss, token, ','); studentId = std::stoi(token);
                std::getline(iss, token, ','); studentDuringLesson = std::stoi(token);
                std::getline(iss, token, ','); lessonId = atoi(token.c_str());

                PersonPtr student = std::make_shared<Person>(studentFirstName, studentLastName, studentId, studentDuringLesson, lessonId);
                LessonPtr lesson = std::make_shared<IndividualLesson>(teacher, beginTime, endTime, baseCost, subject, classRoom, student);
                repository->add(lesson, true);

            } else if (lessonType == "GROUP") {
                std::vector<PersonPtr> students;
                while (true) {
                    std::string firstName, lastName;
                    int idStr, lessonIdStr;
                    bool duringStr;
                    if (!std::getline(iss, token, ',')){ break; } firstName = token;
                    std::getline(iss, token, ','); lastName = token;
                    std::getline(iss, token, ','); idStr = atoi(token.c_str());
                    std::getline(iss, token, ','); duringStr = atoi(token.c_str());
                    std::getline(iss, token, ','); lessonIdStr = atoi(token.c_str());

                    auto student = std::make_shared<Person>(firstName, lastName, idStr, duringStr, lessonIdStr);
                    students.push_back(student);
                }

                auto lesson = std::make_shared<GroupLesson>(teacher, beginTime, endTime, baseCost, subject, classRoom);
                for (auto& s : students) {
                    lesson->addStudent(s);
                }
                repository->add(lesson, true);
            } else {
                throw std::runtime_error("Nieznany typ lekcji: " + lessonType);
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Błąd konwersji danych w archiwum: " << line << " -> " << e.what() << std::endl;
        }
        catch (const std::exception& e) {
            std::cerr << "Inny błąd podczas przetwarzania archiwum: " << line << " -> " << e.what() << std::endl;
        }
    }

    inputFile.close();
    return true;
}

void LessonFilesStorage::saveArchive(const LessonRepositoryPtr &lessonRepo, const int id) {
    const std::string fileName = "./../../archive/lessons/Lesson.txt";
    std::ofstream outFile(fileName, std::ios::app);

    if (!outFile.is_open()) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }

    const LessonPtr lesson = lessonRepo->findByIndex(id);

    if (lesson ==  nullptr) {
        throw std::logic_error("Blad, nie ma takiej lekcji");
    }

    outFile << lesson->getAttributes() << std::endl;
    outFile.close();

    std::cout << "Zapis do archiwum przebiegl pomyslnie" << std::endl;
}

void LessonFilesStorage::showArchive() {
    const std::string fileName = "./../../archive/lessons/Lesson.txt";
    std::ifstream inputFile(fileName);

    if (!inputFile) {
        throw std::runtime_error("Blad otwierania pliku " + fileName);
    }

    std::cout << std::endl;
    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
}
