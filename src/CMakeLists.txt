include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/Model
    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Strategies
    ${CMAKE_CURRENT_SOURCE_DIR}/View
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_library(src_Practicum3
    main.cpp
    view/edgeview.h view/edgeview.cpp
    view/vertexview.h view/vertexview.cpp
    view/graphwidget.h view/graphwidget.cpp
    view/mainWidget.h view/mainWidget.cpp
    view/datalistview.h view/datalistview.cpp

    model/graphdata.h model/graphdata.cpp
    model/Strategies/strategy1.h model/Strategies/strategy1.cpp
    model/strategyfactory.h model/strategyfactory.cpp
    model/vertex.h model/vertex.cpp
    model/strategycontext.h model/strategycontext.cpp
    model/basestrategy.h model/basestrategy.cpp
    model/repository.h model/repository.cpp
)

file(REMOVE ${CMAKE_BINARY_DIR}/src/data)
file(COPY ${CMAKE_SOURCE_DIR}/src/data DESTINATION ${CMAKE_BINARY_DIR}/src)

target_link_libraries(src_Practicum3 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
