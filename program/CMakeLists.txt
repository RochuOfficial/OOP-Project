cmake_minimum_required(VERSION 3.4)

project(Program)

# Ustaw we własnej zmiennej SOURCE_FILES zbiór plików źródłowych projektu
set(SOURCE_FILES src/main.cpp
        src/peopleFunctions.cpp
        include/peopleFunctions.h
        include/groupsFunctions.h
        src/classRoomFunctions.cpp
        include/classRoomFunctions.h
        include/archiveFunctions.h
        src/lessonFunctions.cpp
        include/lessonFunctions.h)

# Włącz powyższy zbiór plików do zbudowania programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})

# Określenie zależności pomiędzy projektami Program i MathLibrary
target_link_libraries(Program Library)

# Dołącz katalog include podprojektu Program do globalnej listy. Dzięki temu każdy inny podprojekt będzie ten katalog "widział"
target_include_directories(Program PUBLIC include)
