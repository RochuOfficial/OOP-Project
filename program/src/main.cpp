#include <iostream>
#include <limits>
#include "../../program/include/peopleFunctions.h"
#include "../../program/include/classRoomFunctions.h"
#include "../../program/include/lessonFunctions.h"
#include "interfaces/LessonUI.h"
#include "interfaces/PersonUI.h"
#include "interfaces/ClassRoomUI.h"
#include "managers/LessonManager.h"
#include "managers/PersonManager.h"
#include "managers/ClassRoomManager.h"
#include "repositories/LessonRepository.h"
#include "storages/LessonFilesStorage.h"
#include "storages/PersonFilesStorage.h"
#include "storages/ClassRoomFilesStorage.h"

using namespace std;


void clearCinBuffer();
void mainMenu();

int main(){

    auto personRepository = std::make_shared<PersonRepository>();
    auto personFiles = std::make_shared<PersonFilesStorage>();
    auto personManager = std::make_shared<PersonManager>(personRepository, personFiles);
    const auto personUI = std::make_shared<PersonUI>(personManager);

    auto classRoomRepository = std::make_shared<ClassRoomRepository>();
    auto classRoomFiles = std::make_shared<ClassRoomFilesStorage>();
    auto classRoomManager = std::make_shared<ClassRoomManager>(classRoomRepository, classRoomFiles);
    const auto classRoomUI = std::make_shared<ClassRoomUI>(classRoomManager);

    auto lessonRepository = std::make_shared<LessonRepository>();
    auto lessonFiles = std::make_shared<LessonFilesStorage>();
    auto lessonManager = std::make_shared<LessonManager>(lessonRepository, lessonFiles, personRepository, classRoomRepository);
    const auto lessonUI = std::make_shared<LessonUI>(lessonManager);

    personUI->load();
    classRoomUI->load();
    lessonUI->load();

    int choice;

    while (true) {
        lessonUI->shouldStart();
        lessonUI->shouldEnd();
        mainMenu();
        while (true) {
            cin >> choice;

            if (cin.fail()) {
                clearCinBuffer();
                cout << "Podaj poprawna opcje!" << endl;
                cout << "Wybierz: ";
            }
            else break;
        }

        switch (choice) {
            case 1:
                students::main(personUI, lessonUI);
                lessonUI->shouldStart();
                lessonUI->shouldEnd();
                break;
            case 2:
                classRoom::main(classRoomUI, lessonUI);
                lessonUI->shouldStart();
                lessonUI->shouldEnd();
                break;
            case 3:
                lesson::main(personManager, classRoomManager, lessonUI);
                lessonUI->shouldStart();
                lessonUI->shouldEnd();
                break;

        case 0:
                std::cout << std::endl;
                personUI->save();
                classRoomUI->save();
                lessonUI->save();
                cout << "Wylaczanie aplikacji..." << endl;
                return 0;

            default:
                cout << "Wybierz poprawna opcje!" << endl;
                break;
        }
    }
}


void clearCinBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mainMenu() {
    cout << endl;
    cout << "=============================================" << endl;
    cout << "=            Centrum Szkoleniowe            =" << endl;
    cout << "=============================================" << endl;
    cout << "1. Operacje zwiazane ze osobami" << endl;
    cout << "2. Operacje zwiazane z salami" << endl;
    cout << "3. Operacje zwiazane z lekcjami" << endl;
    cout << "0. Wylacz aplikacje" << endl;
    cout << "Wybierz: ";
}
