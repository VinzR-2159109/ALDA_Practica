cmake_minimum_required(VERSION 3.24)
project(ALDA_Practicum1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ALDA_Practicum1 main.cpp
        contact.cpp contact.h
        addressBookV1.cpp addressBookV1.h
        repository.h repository.cpp
        consolemenu.h consolemenu.cpp
        variant1.h variant1.cpp
        variant3.h variant3.cpp
        addressbookv3.h addressbookv3.cpp
)
