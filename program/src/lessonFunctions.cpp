#include "../include/lessonFunctions.h"
#include "interfaces/LessonUI.h"
#include "typedefs.h"
#include <iostream>
#include <limits>


using namespace std;

namespace lesson {
    void clearCinBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void main(const PersonManagerPtr& personManager, const ClassRoomManagerPtr& classRoomManager, const LessonUIPtr& lessonUI) {
        int choice;

        while (true) {
            lessonUI->shouldStart();
            lessonUI->shouldEnd();
            menu();
            while (true) {
                cin >> choice;

                if (cin.fail()) {
                    clearCinBuffer();
                    cout << "Wybierz poprawna opcje!" << endl;
                    cout << "Wybierz: ";
                }

                else break;
            }

            switch (choice) {
                case 1:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    lessonUI->showStartedLessons();
                    break;

                case 2:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    lessonUI->showPlannedLessons();
                    break;

                case 3:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    lessonUI->showArchive();
                    break;

                case 4:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    lessonUI->startLesson(personManager, classRoomManager);
                    break;
                case 0:
                    return;

                default:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    cout << "Wybierz wlasciwa opcje!" << endl;
                    break;
            }
        }
    }

    void menu() {
        cout << endl;
        cout << "=============================================" << endl;
        cout << "=                   Lekcje                  =" << endl;
        cout << "=============================================" << endl;
        cout << "1. Wyswietl rozpoczete lekcje" << endl;
        cout << "2. Wyswietl zaplanowane lekcje" << endl;
        cout << "3. Wyswietl archiwalne lekcje" << endl;
        cout << "4. Rozpocznij nowa lekcje" << endl;
        cout << "0. Wroc do menu glownego" << endl;
        cout << "Wybierz: ";
    }
}
