#include "interfaces/LessonUI.h"
#include "managers/PersonManager.h"
#include "managers/ClassRoomManager.h"
#include "managers/LessonManager.h"
#include "typedefs.h"
#include <string>
#include <boost/date_time.hpp>
#include <utility>

namespace pt = boost::posix_time;


LessonUI::LessonUI(LessonManagerPtr  manager) : manager(std::move(manager)) {
}

void LessonUI::startLesson(const PersonManagerPtr& personManager, const ClassRoomManagerPtr& classRoomManager) const {
    int choice = -1;
    int startTimeChoice = -1;
    int teacherID;
    int studentID;
    int classRoomNumber;
    int baseLessonCost;
    std::string lessonSubject;
    std::string customLessonStart;
    std::string customLessonEnd;
    pt::ptime startTime;
    pt::ptime endTime;
    const std::vector<PersonPtr> people = personManager->findAllPersons();
    const std::vector<ClassRoomPtr> classRooms = classRoomManager->findAllClassRooms();
    auto availablePersons = personManager->findPersons([](const PersonPtr& person) {
        return !person->isDuringLesson();
    });
    const auto availableClassRooms = classRoomManager->findClassRooms([](const ClassRoomPtr& classRoom) {
        return classRoom->isAvailable();
    });
    PersonPtr teacher;
    PersonPtr student;
    ClassRoomPtr classRoom;

    // if (people.empty()) {
    //     std::cout << std::endl << "Znanim rozpoczniesz lekcje, dodaj nowe osoby!" << std::endl;
    //     return;
    // }
    //
    // if (availablePersons.size() < 2) {
    //     std::cout << std::endl << "Jest za malo dostepnych osob aby rozpoczac lekcje!" << std::endl;
    //     return;
    // }
    //
    // if (availableClassRooms.empty()) {
    //     std::cout << std::endl << "Jest za malo dostepnych sal aby rozpoczac lekcje!" << std::endl;
    //     return;
    // }

    while (choice != 0) {
        shouldStart();
        shouldEnd();
        availablePersons = personManager->findPersons([](const PersonPtr& person) {
            return !person->isDuringLesson();
        });
        // auto availablePersons2 = personManager->findPersons([](const PersonPtr& person) {
        //     return !person->isDuringLesson();
        // });
        // auto availableClassRooms2 = classRoomManager->findClassRooms([](const ClassRoomPtr& classRoomI) {
        //     return classRoomI->isAvailable();
        // });
        // if (availableClassRooms2.empty()) {
        //     std::cout << "Brak dostepnych sal" << std::endl;
        //     break;
        // }

        std::cout << std::endl << "Jaka lekcje chcesz zaplanowac?" << std::endl;
        std::cout << "1. Indywidualna" << std::endl;
        std::cout << "2. Grupowa" << std::endl;
        std::cout << "0. Wroc" << std::endl;
        std::cout << ">> ";
        while (true) {
            std::cin >> choice;

            if (std::cin.fail() || choice < 0 || choice > 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                std::cout << ">> ";
            }
            else if (choice == 2 && availablePersons.size() < 3) {
                std::cout << "Brak wystarczajacej liczby dostepnych osob" << std::endl;
                choice = 0;
                break;
            }
            else break;
        }

        if (choice == 0) return;

        // -------- Setting Lesson Start Time --------
        std::cout << std::endl << "Wybierz czas rozpoczecia lekcji:" << std::endl;
        std::cout << "1. Teraz" << std::endl;
        std::cout << "2. Pozniej" << std::endl;
        std::cout << ">> ";
        while (true) {
            std::cin >> startTimeChoice;
            if (std::cin.fail() || startTimeChoice < 1 || startTimeChoice > 2) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                std::cout << ">> ";
            }

            else break;
        }

        bool now = false;
        if (startTimeChoice == 1) {
            startTime = pt::second_clock::local_time();
            now = true;
        }
        else {
            std::cout << std::endl << "Podaj date w formacie \"YYYY-MM-DD HH:MM:SS\": " << std::endl;
            std::cout << ">> ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            while (true) {
                std::getline(std::cin, customLessonStart);

                try {
                    startTime = pt::time_from_string(customLessonStart);
                    if (startTime <= pt::second_clock::local_time()) {
                        std::cout << "Podaj date i godzine z przyszlosci!" << std::endl;
                        std::cout << ">> ";
                        continue;
                    }
                    break;
                }
                catch (const std::exception& e) {
                    std::cout << "Podany format jest nieprawidlowy!" << std::endl;
                    std::cout << "Oczekiwany format \"YYYY-MM-DD HH:MM:SS\"" << std::endl;
                    std::cout << ">> ";
                }
            }
        }

        // -------- Setting Lesson End Time --------
        int minutes;
        std::cout << std::endl << "Podaj czas trwania lekcji (w minutach):" << std::endl;
        std::cout << ">> ";
        while (true) {
            std::cin >> minutes;

            if (std::cin.fail() || minutes < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Czas trwania lekcji musi byc dodania liczba calkowita!" << std::endl;
                std::cout << ">> ";
            }
            else {
                pt::time_duration lessonDuration = pt::minutes(minutes);
                endTime = startTime + lessonDuration;
                break;
            }
        }

        if (now) {
            availablePersons = personManager->findPersons([](const PersonPtr& person) {
                return !person->isDuringLesson();
            });
        }
        else {
            availablePersons = personManager->findPersons([&startTime, &endTime](const PersonPtr& person) {
                for (const auto& lesson : person->getFutureLessons()) {
                    if (lesson->getBeginTime() < endTime && lesson->getEndTime() > startTime) {
                        return false;
                    }
                }
                return true;
            });
        }

        if (choice==1 && availablePersons.size() < 2) {
            std::cout << "Brak wystarczajacej ilosci osob w tym czasie" << std::endl;
            return;
        }

        if (choice==2 && availablePersons.size() < 3) {
            std::cout << "Brak wystarczajacej ilosci osob w tym czasie" << std::endl;
            return;
        }

        // -------- Setting Lesson Subject --------
        std::cout << std::endl << "Podaj temat lekcji" << std::endl;
        std::cout << ">> ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, lessonSubject);

        // -------- Choosing Lesson Class Room --------
        std::cout << std::endl << "Wybierz sale:" << std::endl;
        for (const ClassRoomPtr& classRoomI : classRooms) {
            std::cout << classRoomI->getNumber() << ". " << classRoomI->getInfo() << std::endl;
        }
        std::cout << ">> ";
        while (true) {
            std::cin >> classRoomNumber;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                std::cout << ">> ";
                continue;
            }

            classRoom = classRoomManager->getClassRoom(classRoomNumber);

            if (!classRoom) {
                std::cout << "Taka sala nie istnieje!" << std::endl;
                std::cout << ">> ";
            }

            else break;
        }

        // -------- Setting Lesson Base Cost --------
        std::cout << std::endl << "Podaj koszt lekcji" << std::endl;
        std::cout << ">> ";
        while (true) {
            std::cin >> baseLessonCost;

            if (std::cin.fail() || baseLessonCost < 1) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Koszt lekcji musi byc dodania liczba calkowita!" << std::endl;
                std::cout << ">> ";
            }

            else break;
        }

        // -------- Choosing Lesson Teacher --------
        std::cout << std::endl << "Wybierz nauczyciela:" << std::endl;
        for (const PersonPtr& person : availablePersons) {
            std::cout << person->getId() << ". " << person->getInfo() << std::endl;
        }
        std::cout << ">> ";
        while (true) {
            std::cin >> teacherID;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                std::cout << ">> ";
                continue;
            }

            teacher = personManager->getPerson(teacherID);

            if (!teacher) {
                std::cout << "Taka osoba nie istnieje!" << std::endl;
                std::cout << ">> ";
                continue;
            }

            if (teacher->isDuringLesson()) {
                std::cout << "Ta osoba jest juz w trakcie lekcji!" << std::endl;
                std::cout << ">> ";
            }

            else break;
        }

        if (now) {
            availablePersons = personManager->findPersons([teacherID](const PersonPtr& person) {
                return !person->isDuringLesson() && person->getId() != teacherID;
            });
        }
        else {
            availablePersons = personManager->findPersons([&startTime, &endTime, &teacherID](const PersonPtr& person) {
                for (const auto& lesson : person->getFutureLessons()) {
                    if (person->getId() == teacherID) continue;
                    if (lesson->getBeginTime() < endTime && lesson->getEndTime() > startTime) {
                        return false;
                    }
                }
                return true;
            });
        }

        switch (choice) {
        case 1:
            // -------- Choosing Lesson Student --------
            std::cout << std::endl << "Wybierz ucznia:" << std::endl;
            for (const PersonPtr& person : availablePersons) {
                std::cout << person->getId() << ". " << person->getInfo() << std::endl;
            }
            std::cout << ">> ";
            while (true) {
                std::cin >> studentID;

                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                    std::cout << ">> ";
                    continue;
                }

                if (studentID == teacherID) {
                    std::cout << "Nauczyciel nie moze byc jednoczesnie uczniem!" << std::endl;
                    std::cout << ">> ";
                    continue;
                }

                student = personManager->getPerson(studentID);

                if (!student) {
                    std::cout << "Taka osoba nie istnieje!" << std::endl;
                    std::cout << ">> ";
                    continue;
                }

                if (student->isDuringLesson()) {
                    std::cout << "Ta osoba jest juz w trakcie lekcji!" << std::endl;
                    std::cout << ">> ";
                }

                else break;
            }
            if (manager->addIndividualLesson(teacher, startTime, endTime, baseLessonCost, lessonSubject, classRoom,
                                             student, now))
                std::cout << "Lekcja zapisana!" << std::endl;
            else
                std::cerr << "Blad podczas tworzenia lekcji!" << std::endl;
            break;

        case 2: {
            const LessonPtr newLesson = manager->addGroupLesson(teacher, startTime, endTime, baseLessonCost,
                                                                lessonSubject, classRoom, now);
            int newLessonID = newLesson->getID();
            char moreStudents = 't';
            std::vector<int> chosenIds;

            // -------- Choosing Lesson Students --------
            while (moreStudents == 't' || moreStudents == 'T') {

                std::cout << std::endl << "Wybierz ucznia:" << std::endl;
                for (const PersonPtr& person : availablePersons) {
                    std::cout << person->getId() << ". " << person->getInfo() << std::endl;
                }
                std::cout << ">> ";
                while (true) {
                    std::cin >> studentID;

                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                        std::cout << ">> ";
                        continue;
                    }

                    if (studentID == teacherID) {
                        std::cout << "Nauczycuel nie moze byc jednoczesnie studentem!" << std::endl;
                        std::cout << ">> ";
                        continue;
                    }

                    student = personManager->getPerson(studentID);

                    if (!student) {
                        std::cout << "Taka osoba nie istnieje!" << std::endl;
                        std::cout << ">> ";
                        continue;
                    }

                    if (student->isDuringLesson()) {
                        std::cout << "Ta osoba jest juz w trakcie lekcji!" << std::endl;
                        std::cout << ">> ";
                        continue;
                    }

                    if (std::any_of(chosenIds.begin(), chosenIds.end(),
                                    [studentID](const int x) { return x == studentID; })) {
                        std::cout << "Ta osoba zostala juz wybrana!" << std::endl;
                        std::cout << ">> ";
                                    }

                    else {
                        chosenIds.push_back(studentID);
                        student->addFutureLesson(newLesson);
                        break;
                    }
                }

                if (manager->addStudentToGroupLesson(newLessonID, personManager->getPerson(studentID)) != 0)
                    std::cerr << "Blad podczas dodawania ucznia do lekcji!" << std::endl;

                if (now) {
                    availablePersons = personManager->findPersons([](const PersonPtr& person) {
                        return !person->isDuringLesson();
                    });
                }
                else {
                    availablePersons = personManager->findPersons([&startTime, &endTime](const PersonPtr& person) {
                        for (const auto& lesson : person->getFutureLessons()) {
                            if (lesson->getBeginTime() < endTime && lesson->getEndTime() > startTime) {
                                return false;
                            }
                        }
                        return true;
                    });
                }

                if (!availablePersons.empty()) {
                    std::cout << std::endl << "Uczen dodany!" << std::endl;
                    while (true) {
                        std::cout << "Chcesz dodac kolejnego ucznia? (t/n):" << std::endl;
                        std::cout << ">> ";
                        std::cin >> moreStudents;

                        if (std::cin.fail() || (moreStudents != 't' && moreStudents != 'T' && moreStudents != 'n' && moreStudents !=
                            'N')) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Wybierz wlasciwa opcje!" << std::endl;
                            std::cout << ">> ";
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    std::cout << "Nie mozna dodac wiecej uczniow" << std::endl;
                    break;
                }
            }

            chosenIds.clear();
            std::cout << "Lekcja zapisana!" << std::endl;
            break;
        }
            default:
                break;
        }
    }
}

void LessonUI::endLesson() const {
    LessonPtr lesson;
    int lessonID;
    const std::vector<LessonPtr> lessons = manager->findAllLessons();

    if (lessons.empty()) {
        std::cout << std::endl << "Nie ma zadnych rozpoczetych lekcji!" << std::endl;
        return;
    }

    std::cout << std::endl << "Podaj ID lekcji:" << std::endl;
    for (const LessonPtr& lessonI : lessons) {
        std::cout << lessonI->getID() << ". " << lessonI->getInfo() << std::endl;
    }
    std::cout << ">> ";
    while (true) {
        std::cin >> lessonID;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wybierz wlasciwa opcje!" << std::endl;
            std::cout << ">> ";
            continue;
        }

        lesson = manager->getLesson(lessonID);

        if (!lesson) {
            std::cout << std::endl << "Nie ma takiej lekcji!" << std::endl;
            std::cout << ">> ";
        }

        else break;
    }

    if (manager->finishLesson(lessonID)) {
        std::cout << std::endl << "Lekcja o ID: " << lessonID << " zakonczona." << std::endl;
        std::cout << "Jej koszt to: " << lesson->getTotalCost() << std::endl;
    }
}

void LessonUI::showStartedLessons() const {
    const std::vector<LessonPtr> lessons = manager->findStartedLessons();

    if (lessons.empty()) {
        std::cout << std::endl << "Nie ma zadnych rozpoczetych lekcji!" << std::endl;
        return;
    }

    std::cout << std::endl;
    for (const LessonPtr& lesson : lessons) {
        std::cout << lesson->getID() << ". " << lesson->getInfo() << std::endl;
    }
}

void LessonUI::showPlannedLessons() const {
    const std::vector<LessonPtr> lessons = manager->findPlannedLessons();

    if (lessons.empty()) {
        std::cout << std::endl << "Nie ma zadnych zaplanowanych lekcji!" << std::endl;
        return;
    }

    std::cout << std::endl;
    for (const LessonPtr& lesson : lessons) {
        std::cout << lesson->getID() << ". " << lesson->getInfo() << std::endl;
    }
}

void LessonUI::save() const {
    if (manager->save()) {
        std::cout << "Zapis lekcji przebiegl pomyslnie" << std::endl;
    }
    else {
        std::cerr << "Nie udalo sie zapisac osob" << std::endl;
    }
}

void LessonUI::load() const {
    if (manager->load()) {
        std::cout << "Odczyt lekcji przebiegl pomyslnie" << std::endl;
    }
    else {
        std::cerr << "Nie udalo sie zapisac lekcji" << std::endl;
    }
}

void LessonUI::showArchive() const {
    manager->showArchive();
}

void LessonUI::shouldStart() const {
    const std::vector<LessonPtr> lessons = manager->findLessons([](const LessonPtr& lesson) {
        return !lesson->isStarted();
    });
    for (const LessonPtr& lessonI : lessons) {
        if (lessonI->getBeginTime() < pt::second_clock::local_time()) {
            if (!manager->startLesson(lessonI->getID())) {
                std::cout << "Nie udalo sie zakonczyc lekcji: " << lessonI->getID() << std::endl;
            }
        }
    }
}

void LessonUI::shouldEnd() const {
    const std::vector<LessonPtr> lessons = manager->findLessons([](const LessonPtr& lesson) {
        return lesson->isStarted();
    });

    for (const LessonPtr& lessonI : lessons) {
        if (lessonI->getEndTime() < pt::second_clock::local_time()) {
            if (!manager->finishLesson(lessonI->getID())) {
                std::cout << "Nie udalo sie zakonczyc lekcji: " << lessonI->getID() << std::endl;
            }
        }
    }
}