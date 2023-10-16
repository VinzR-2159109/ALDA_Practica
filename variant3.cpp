#include "variant3.h"

#include <iostream>

void Variant3::start()
{
    // load contacts from file
    AddressBookV3 addressBook = AddressBookV3();
    addressBook.addContactsFromFile("../ContactsData.txt");

    // create console menu
    std::vector<std::string> menuOptions = {
        "Hallo",
        "Bonjour",
        "Exit"
    };
    ConsoleMenu menu = ConsoleMenu(menuOptions);

    // loop until exit
    while (true) {
        menu.drawMenu();
        char option = menu.getOption();

        if (option < '1' || option > '3') {
            std::cout << "Error: option " << option << " is invalid\n\n";
            continue;
        }

        switch (option) {
        case '1':
            handleGetByName(menu, addressBook);
            break;
        case '2':
            handleDeleteByName(menu, addressBook);
            break;
        case '3':
            return;
        }
    }
}

void Variant3::handleGetByName(ConsoleMenu &menu, AddressBookV3 &addressBook)
{
    std::string name = menu.getString("name");
    const Contact *contact = addressBook.getContactByName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    menu.printContact(*contact);
}

void Variant3::handleDeleteByName(ConsoleMenu &menu, AddressBookV3 &addressBook)
{
    std::string name = menu.getString("name");
    addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}
