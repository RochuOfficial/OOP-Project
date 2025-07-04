#include "interfaces/ClassRoomUI.h"
#include "model/EngClassRoom.h"
#include "model/ITClassRoom.h"
#include "model/MathClassRoom.h"
#include "managers/ClassRoomManager.h"
#include <iostream>
#include <string>
#include <utility>


void error1() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Podaj poprawna wartosc" << std::endl;
}

bool getYesNo(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string input;
        std::cin >> input;
        if (input == "t" || input == "T") return true;
        if (input == "n" || input == "N") return false;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Podaj 't' lub 'n'" << std::endl;
    }
}

ClassRoomUI::ClassRoomUI(ClassRoomManagerPtr classRoomManager)
    : classRoomManager(std::move(classRoomManager))
{
}

void ClassRoomUI::showAvailableClassRooms() const {
    const auto availableRooms = classRoomManager->findClassRooms([](const ClassRoomPtr& room) {
    return room->isAvailable();
    });

    if (availableRooms.empty()) {
        std::cout << std::endl << "Brak dostepnych sal" << std::endl;
    }

    std::cout << std::endl;
    for (const auto& room : availableRooms) {
        std::cout << room->getNumber() << ". " << room->getInfo() << std::endl;
    }
}

void ClassRoomUI::showArchive() const {
    const std::vector<ClassRoomPtr> classRooms = classRoomManager->getArchive();

    if (classRooms.empty()) {
        std::cout << std::endl << "Brak sal w archiwum" << std::endl;
        return;
    }

    std::cout << std::endl;
    for (const auto& room : classRooms) {
        std::cout << room->getNumber() << ". " << room->getInfo() << std::endl;
    }
}

void ClassRoomUI::restore() const {
    int number;
    const std::vector<ClassRoomPtr> classRooms = classRoomManager->getArchive();

    if (classRooms.empty()) {
        std::cout << std::endl << "Brak sal do przywrocenia" << std::endl;
        return;
    }

    while (true) {
        std::cout << std::endl << "Sale do przywrocenia: " << std::endl;
        for (auto& room : classRooms) {
            std::cout << room->getNumber() << ". " << room->getInfo() << std::endl;
        }

        std::cout << "Wybierz numer: ";
        std::cin >> number;

        if (std::cin.fail() || number < 0) {
            error1();
            continue;
        }

        bool exist = false;
        for (auto& room : classRooms) {
            if (room->getNumber() == number) {
                exist = true;
                break;
            }
        }

        if (!exist) {
            std::cout << "Taka sala nie istnieje" << std::endl;
        } else {
            classRoomManager->loadArchive(number);
            break;
        }
    }
}

void ClassRoomUI::save() const {
    if (classRoomManager->saveClassRooms()) {
        std::cout << "Zapis sal przebiegl pomyslnie" << std::endl;
    } else {
        std::cerr << "Nie udalo sie zapisac sal" << std::endl;
    }
}

void ClassRoomUI::load() const {
    if (classRoomManager->loadClassRooms()) {
        std::cout << "Odczyt sal przebiegl pomyslnie" << std::endl;
    } else {
        std::cerr << "Nie udalo sie odczytac sal" << std::endl;
    }
}

void ClassRoomUI::addClassRoom() const {
    std::string type;
    int number, seatsNumber;
    double rentCost;
    ClassRoomTypePtr classRoomType;

    while (true) {
        std::cout << std::endl << "Wybierz typ klasy (IT, MATH, ENG): ";
        std::cin >> type;

        if (type == "IT") {
            while (true) {
                int computers;
                std::cout << "Liczba komputerów: ";
                std::cin >> computers;
                if (std::cin.fail() || computers < 0) {
                    error1();
                } else {
                    classRoomType = std::make_shared<ITClassRoom>(computers);
                    break;
                }
            }
        } else if (type == "MATH") {
            bool formulasTables = getYesNo("Czy sa tablice matematyczne (t/n)? ");
            classRoomType = std::make_shared<MathClassRoom>(formulasTables);
        } else if (type == "ENG") {
            bool headphones = getYesNo("Czy sa sluchawki (t/n)? ");
            classRoomType = std::make_shared<EngClassRoom>(headphones);
        } else {
            std::cout << "Nieznany typ sali." << std::endl;
            continue;
        }

        break;
    }

    while (true) {
        std::cout << "Numer sali: ";
        std::cin >> number;

        if (std::cin.fail() || number < 0) {
            error1();
            continue;
        }

        if (classRoomManager->getClassRoom(number)) {
            std::cout << "Podany numer jest zajety" << std::endl;
            continue;
        }
        break;
    }

    while (true) {
        std::cout << "Liczba miejsc: ";
        std::cin >> seatsNumber;
        if (std::cin.fail() || seatsNumber < 0) {
            error1();
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Koszt wynajmu: ";
        std::cin >> rentCost;
        if (std::cin.fail() || rentCost < 0) {
            error1();
        } else {
            break;
        }
    }

    if (classRoomManager->addClassRoom(number, true, seatsNumber, rentCost, classRoomType))
        std::cout << "Klasa zostala dodana" << std::endl;
    else
        std::cerr << "Blad przy dodawaniu klasy!" << std::endl;
}

void ClassRoomUI::removeClassRoom() const {
    int number;
    const auto availableRooms = classRoomManager->findClassRooms([](const ClassRoomPtr& room) {
            return room->isAvailable();
    });

    if (const int size = static_cast<int>(availableRooms.size()); size == 0) {
        std::cout << std::endl << "Brak dostepnych sal do usuniecia" << std::endl;
        return;
    }

    while (true) {
        showAvailableClassRooms();
        std::cout << std::endl << "Wybierz numer sali do usuniecia: ";
        std::cin>>number;
        if (std::cin.fail() || number < 0) {
            error1();
            continue;
        }
        bool isAvailable = false;
        for (auto& room : availableRooms) {
            if (room->getNumber() == number) {
                isAvailable = true;
            }
        }
        if (!isAvailable) {
            std::cout << "Podany numer nie jest dostepny lub nie ma go w systemie" << std::endl;
        } else {
            if (classRoomManager->getClassRoom(number)) {
                classRoomManager->removeClassRoom(number);
                break;
            }
            error1();
        }
    }
}

void ClassRoomUI::showClassRooms() const {
    if (classRoomManager->report().empty()) {
        std::cout << std::endl << "Brak sal w systemie" << std::endl;
        return;
    }

    std::cout << std::endl << classRoomManager->report();
}
