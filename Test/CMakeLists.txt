find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest-src
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(test_Practicum3
    main.cpp
    tst_bfs.cpp
    tst_reachablematrix.cpp
    tst_topologicaorder.cpp
)

file(REMOVE ${CMAKE_BINARY_DIR}/test/data)
file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR}/test)

target_link_libraries(test_Practicum3 PRIVATE
    gtest
    gmock
    Qt${QT_VERSION_MAJOR}::Widgets
    src_Practicum3
)
