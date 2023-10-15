#include <iostream>
#include "AddressBookV1.h"
#include "consolemenu.h"

void handleGetByName(ConsoleMenu &menu, AddressBookV1 &addressBook);
void handleDeleteByName(ConsoleMenu &menu, AddressBookV1 &addressBook);

int main()
{
    // load contacts from file
    AddressBookV1 addressBook = AddressBookV1();
    addressBook.addContactsFromFile("../ContactsData.txt");

    ConsoleMenu menu = ConsoleMenu();

    bool exit = false;
    while (exit == false) {
        menu.drawMenu();
        ConsoleMenu::MenuOption option = menu.getOption();

        switch (option) {
        case ConsoleMenu::MenuOption::GET_FULL_NAME:
            handleGetByName(menu, addressBook);
            break;
        case ConsoleMenu::MenuOption::DELETE_FULL_NAME:
            handleDeleteByName(menu, addressBook);
            break;
        case ConsoleMenu::MenuOption::EXIT:
            exit = true;
            break;
        default:
            break;
        }
    }

    return 0;
}

void handleGetByName(ConsoleMenu &menu, AddressBookV1 &addressBook)
{
    std::string name = menu.getString();
    const Contact *contact = addressBook.getContactByName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    menu.printContact(*contact);
}

void handleDeleteByName(ConsoleMenu &menu, AddressBookV1 &addressBook)
{
    std::string name = menu.getString();
    addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}

