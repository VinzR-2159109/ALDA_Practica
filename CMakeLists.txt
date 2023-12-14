cmake_minimum_required(VERSION 3.5)

project(Practicum3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(".")

set(PROJECT_SOURCES
    main.cpp
)

qt_add_executable(Practicum3
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    View/edgeview.h View/edgeview.cpp
    View/vertexview.h View/vertexview.cpp
    View/graphwidget.h View/graphwidget.cpp
    View/mainWidget.h View/mainWidget.cpp
    Model/vertex.h Model/vertex.cpp
    Model/strategycontext.h Model/strategycontext.cpp
    Model/basestrategy.h Model/basestrategy.cpp
    Model/repository.h Model/repository.cpp
    View/datalistview.h View/datalistview.cpp
    Model/graphdata.h Model/graphdata.cpp
    Model/Strategies/strategy1.h Model/Strategies/strategy1.cpp
    Model/strategyfactory.h Model/strategyfactory.cpp
    Model/Strategies/topologicalorder.h Model/Strategies/topologicalorder.cpp

)

target_link_libraries(Practicum3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

find_package(Qt6 REQUIRED COMPONENTS Test)
target_link_libraries(Practicum3 PRIVATE Qt${QT_VERSION_MAJOR}::Test)

file(COPY ${CMAKE_SOURCE_DIR}/Data DESTINATION ${CMAKE_BINARY_DIR})

include(GNUInstallDirs)
install(TARGETS Practicum3
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Practicum3)
endif()
