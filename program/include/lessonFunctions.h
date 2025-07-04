#ifndef LESSONFUNCTIONS_H
#define LESSONFUNCTIONS_H

#include "typedefs.h"


namespace lesson {
    void clearCinBuffer();

    void main(const PersonManagerPtr& personManager, const ClassRoomManagerPtr& classRoomManager, const LessonUIPtr& lessonUI);

    void menu();
}


#endif //LESSONFUNCTIONS_H
