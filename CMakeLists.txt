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

qt_add_executable(Practicum3 MANUAL_FINALIZATION)

target_link_libraries(Practicum3 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    src_Practicum3
)

include(GNUInstallDirs)
install(TARGETS Practicum3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Practicum3)
endif()
################### Aplication ##################


##################### GTest #####################
add_subdirectory(test)
##################### GTest #####################
