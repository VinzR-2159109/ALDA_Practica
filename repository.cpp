#include "repository.h"
#include <fstream>
#include <iostream>

std::vector<Contact> dataRepository::loadContacts(std::string fileName)
{
    std::ifstream file;
    std::string constactString;

    file.open(fileName);
    if (!file.is_open()) {
        file.close();
        std::cout << "-- Failed to open file " << fileName << " --\n";
    }

    std::vector<Contact> contacts;

    int counter = 0;
    while (true) {
        if (file.eof())
            break;

        std::string firstName, lastName, address, phoneNumber;

        std::getline(file, firstName, ';');
        std::getline(file, lastName, ';');
        std::getline(file, address, ';');
        std::getline(file, phoneNumber, '\n');

        contacts.emplace_back(firstName, lastName, address, phoneNumber);

        counter++;
        if (counter == 5)
            break;
    }

    file.close();

    return contacts;
}
