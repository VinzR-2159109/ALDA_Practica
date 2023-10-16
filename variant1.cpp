#include "variant1.h"

#include <iostream>

void Variant1::start()
{
    // load contacts from file
    AddressBookV1 addressBook = AddressBookV1();
    addressBook.addContactsFromFile("../ContactsData.txt");

    // create console menu
    std::vector<std::string> menuOptions = {
        "get contact information by full name",
        "delete contact by full name",
        "Exit program"
    };
    ConsoleMenu menu = ConsoleMenu(menuOptions);


    // loop until exit
    while (true) {
        menu.drawMenu();
        char option = menu.getOption();

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

void Variant1::handleGetByName(ConsoleMenu &menu, AddressBookV1 &addressBook)
{
    std::string name = menu.getString("name");
    const Contact *contact = addressBook.getContactByName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    menu.printContact(*contact);
}

void Variant1::handleDeleteByName(ConsoleMenu &menu, AddressBookV1 &addressBook)
{
    std::string name = menu.getString("name");
    addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}
