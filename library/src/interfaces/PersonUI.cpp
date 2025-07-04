#include "interfaces/PersonUI.h"
#include "model/Person.h"
#include "managers/PersonManager.h"
#include <iostream>
#include <string>


void error() {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Podaj poprawna wartosc" << std::endl;
}

PersonUI::PersonUI(const PersonManagerPtr &personManager)
    : personManager(personManager)
{
}

void PersonUI::addPerson() const {
    std::string firstName;
    std::string lastName;
    int id;

    while (true) {
        std::cout << std::endl << "Imie: ";
        std::cin >> firstName;
        if (std::cin.fail() || firstName.empty()) {
            error();
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Nazwisko: ";
        std::cin >> lastName;
        if (std::cin.fail() || lastName.empty()) {
            error();
        } else {
            break;
        }
    }

    while (true) {
        std::cout << "Podaj id: ";
        std::cin >> id;
        if (personManager->getPerson(id)) {
            std::cout << "Podany identyfikator jest zajety" << std::endl;
        } else if (std::cin.fail() || id < 0) {
            error();
        } else {
            break;
        }
    }

    if (personManager->addPerson(firstName, lastName, id))
        std::cout << std::endl << "Osoba " << firstName << " zostala dodana!" << std::endl;
}

void PersonUI::removePerson() const {
    int id;
    const auto availablePersons = personManager->findPersons([](const PersonPtr& person) {
            return !person->isDuringLesson();
    });

    if (const int size = static_cast<int>(availablePersons.size()); size == 0) {
        std::cout << "Brak dostepnych osob do usuniecia" << std::endl;
        return;
    }

    while (true) {
        showAvailablePersons();
        std::cout<<"Wybierz id osoby do usuniecia: ";
        std::cin>>id;
        if (std::cin.fail() || id < 0) {
            error();
            continue;
        }
        bool isAvailable = false;
        for (auto& person : availablePersons) {
            if (person->getId() == id) {
                isAvailable = true;
            }
        }

        if (!isAvailable) {
            std::cout << "Ta osoba nie jest dostepna lub nie ma jej w systemie" << std::endl;
        } else {
            if (personManager->getPerson(id)) {
                personManager->removePerson(id);
                break;
            }

            std::cout << "Podaj odpowiednia liczbe" << std::endl;
        }
    }
}

void PersonUI::showPersons() const {
    if (personManager->report().empty()) {
        std::cout << std::endl << "Brak osob w systemie" << std::endl;
        return;
    }

    std::cout << std::endl << personManager->report();
}

void PersonUI::showAvailablePersons() const {
    const auto availablePersons = personManager->findPersons([](const PersonPtr& person) {
        return !person->isDuringLesson();
    });

    if (availablePersons.empty()) {
        std::cout << std::endl << "Nie ma dostepnych osob" << std::endl;
    }

    std::cout << std::endl;
    for (const auto& person : availablePersons) {
        std::cout << person->getInfo() << std::endl;
    }
}

void PersonUI::showArchive() const {
    const std::vector<PersonPtr> persons = personManager->getArchive();
    if (persons.empty()) {
        std::cout << "Brak osob w archiwum" << std::endl;
    }

    for (const auto& person : persons) {
        std::cout << person->getInfo() << std::endl;
    }
}

void PersonUI::save() const {
    if (personManager->savePersons()) {
        std::cout << "Zapis osob przebiegl pomyslnie" << std::endl;
    } else {
        std::cerr << "Nie udalo sie zapisac osob" << std::endl;
    }
}

void PersonUI::load() const {
    if (personManager->loadPersons()) {
        std::cout << "Odczyt osob przebiegl pomyslnie" << std::endl;
    } else {
        std::cerr << "Nie udalo sie odczytac osob" << std::endl;
    }
}

void PersonUI::restore() const {
    int id;
    const std::vector<PersonPtr> persons = personManager->getArchive();

    if (persons.empty()) {
        std::cout << "Brak osob do przywrocenia" << std::endl;
        return;
    }

    while (true) {
        std::cout << "Osoby do przywrocenia: " << std::endl;
        for (auto& person : persons) {
            std::cout << person->getInfo() << std::endl;
        }

        std::cout << "Wybierz id: ";
        std::cin >> id;

        if (std::cin.fail() || id < 0) {
            error();
            continue;
        }

        bool exist = false;
        for (auto& person : persons) {
            if (person->getId() == id) {
                exist = true;
                break;
            }
        }

        if (!exist) {
            std::cout << "Taka osoba nie istnieje" << std::endl;
        } else {
            personManager->loadArchive(id);
            break;
        }
    }
}
