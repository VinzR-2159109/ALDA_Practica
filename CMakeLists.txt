cmake_minimum_required(VERSION 3.5)

project(Practicum3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

################### Aplication ##################
include_directories(src/model src/view)
add_subdirectory(src)

qt_add_executable(Practicum3 src/main.cpp)

target_link_libraries(Practicum3 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    src_Practicum3
)
################### Aplication ##################


##################### GTest #####################
include_directories(test)
add_subdirectory(test)

add_executable(Practicum3_Test test/main)

#target_link_options(Practicum3_Test PUBLIC "LINKER:--no-as-needed.")
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-as-needed")
target_link_libraries(Practicum3_Test PUBLIC
    gtest
    test_Practicum3
)

include(GoogleTest)
gtest_discover_tests(Practicum3_Test)
##################### GTest #####################
