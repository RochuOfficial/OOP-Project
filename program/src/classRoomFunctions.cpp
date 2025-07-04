#include <iostream>
#include <limits>
#include "../include/classRoomFunctions.h"
#include "interfaces/ClassRoomUI.h"
#include "interfaces/LessonUI.h"

using namespace std;


namespace classRoom {
    void clearCinBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void main(const ClassRoomUIPtr& classRoomUI, const LessonUIPtr& lessonUI) {
        int choice;

        while (true) {
            lessonUI->shouldStart();
            lessonUI->shouldEnd();
            menu();
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
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->showClassRooms();
                    break;
                case 2:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->showAvailableClassRooms();
                    break;
                case 3:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->addClassRoom();
                    break;
                case 4:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->removeClassRoom();
                    break;
                case 5:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->restore();
                    break;
                case 6:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    classRoomUI->showArchive();
                    break;
                case 0:
                    return;

                default:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    cout << "Wybierz porpawna opcje!" << endl;
                    break;
            }
        }
    }

    void menu() {
        cout << endl;
        cout << "=============================================" << endl;
        cout << "=                   Sale                    =" << endl;
        cout << "=============================================" << endl;
        cout << "1. Wyswietl wszystkie sale" << endl;
        cout << "2. Wyswietl dostepne sale" << endl;
        cout << "3. Dodaj sale" << endl;
        cout << "4. Usun sale" << endl;
        cout << "5. Przywroc sale" << endl;
        cout << "6. Wyswietl archiwum sal" << endl;
        cout << "0. Wroc do menu glownego" << endl;
        cout << "Wybierz: ";
    }
}
