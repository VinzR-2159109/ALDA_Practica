#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/googletest-src
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(test_Practicum3
    main.cpp
    tst_strategy1.cpp
)

target_link_libraries(test_Practicum3 PRIVATE
    gtest
    gmock
    Qt${QT_VERSION_MAJOR}::Widgets
    src_Practicum3
)
