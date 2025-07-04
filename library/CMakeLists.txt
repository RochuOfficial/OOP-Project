cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
    src/model/ClassRoom.cpp
    src/model/ClassRoomType.cpp
    src/model/EngClassRoom.cpp
    src/model/ITClassRoom.cpp
    src/model/MathClassRoom.cpp
    src/model/Person.cpp
    src/model/Lesson.cpp
    src/model/GroupLesson.cpp
    src/model/IndividualLesson.cpp
    src/repositories/LessonRepository.cpp
    src/repositories/ClassRoomRepository.cpp
    src/repositories/PersonRepository.cpp
    src/managers/LessonManager.cpp
    src/managers/ClassRoomManager.cpp
    src/managers/PersonManager.cpp
    src/interfaces/ClassRoomUI.cpp
    src/interfaces/LessonUI.cpp
    src/interfaces/PersonUI.cpp
    src/storages/ClassRoomFilesStorage.cpp
    src/storages/PersonFilesStorage.cpp
    src/storages/LessonFilesStorage.cpp
)
# Utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)


enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" "date_time")

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${Boost_INCLUDE_DIRS}
)

target_link_libraries(Library
        ${Boost_DATE_TIME_LIBRARY}
)

set(SOURCE_TEST_FILES
    test/master.cpp
    test/ClassRoomTest.cpp
    test/LessonTest.cpp
    test/PersonTest.cpp
) # tu w przyszłości będą dodawane pliki źródłowe testów

add_executable (LibraryTester ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami oraz bibliotekę boost.test do programu testów
target_link_libraries (LibraryTester
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

#dodaj test LibraryTest. Instrukcji cmake add_test może być wiele.
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(LibraryTest LibraryTester
        --report_level=detailed
        --log_level=all
        --color_output=yes
)

add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})