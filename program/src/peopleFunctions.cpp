#include <iostream>
#include <limits>
#include "typedefs.h"
#include "interfaces/PersonUI.h"
#include "interfaces/LessonUI.h"
#include "../include/peopleFunctions.h"

using namespace std;

namespace students {
    void clearCinBuffer() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    void main(const PersonUIPtr& personUI, const LessonUIPtr& lessonUI) {
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
                    personUI->showPersons();
                    break;
                case 2:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    personUI->showAvailablePersons();
                    break;
                case 3:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    personUI->addPerson();
                    break;
                case 4:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    personUI->removePerson();
                    break;
                case 5:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    personUI->restore();
                    break;
                case 6:
                    lessonUI->shouldStart();
                    lessonUI->shouldEnd();
                    personUI->showArchive();
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
        cout << "==============================================" << endl;
        cout << "=                    Osoby                   =" << endl;
        cout << "==============================================" << endl;
        cout << "1. Wyswietl osoby" << endl;
        cout << "2. Wyswietl dostepne osoby" << endl;
        cout << "3. Dodaj osobe" << endl;
        cout << "4. Usun osobe" << endl;
        cout << "5. Przywroc osobe" << endl;
        cout << "6. Wyswietl archiwum osob" << endl;
        cout << "0. Wroc do menu glownego" << endl;
        cout << "Wybierz: ";
    }
}
