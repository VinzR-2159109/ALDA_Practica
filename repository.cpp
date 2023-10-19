#include "repository.h"
#include <fstream>
#include <iostream>

std::vector<Contact> Repository::loadContacts(std::string fileName)
{
    std::ifstream file;
    std::string constactString;

    file.open(fileName);
    if (!file.is_open()) {
        file.close();
        std::cout << "-- Failed to open file " << fileName << " --\n";
    }

    std::vector<Contact> contacts;

    while (true) {
        if (file.eof())
            break;

        std::string firstName, lastName, address, phoneNumber;

        std::getline(file, firstName, ';');
        std::getline(file, lastName, ';');
        std::getline(file, address, ';');
        std::getline(file, phoneNumber, '\n');

        contacts.emplace_back(firstName, lastName, address, phoneNumber);
    }

    file.close();

    return contacts;
}
