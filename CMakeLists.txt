cmake_minimum_required(VERSION 3.24)
project(ALDA_Practicum1)

set(CMAKE_CXX_STANDARD 17)

add_executable(ALDA_Practicum1 main.cpp
        contact.cpp contact.h
        addressBookV1.cpp addressBookV1.h
        repository.h repository.cpp
        consolemenu.h consolemenu.cpp
        AddressBookV2.cpp
        AddressBookV2.h
)
