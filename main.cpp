#include <iostream>
#include <limits>
#include "AddressBookV1.h"
#include "AddressBookV2.h" // Voeg AddressBookV2 toe
#include "consolemenu.h"

void handleGetByName(ConsoleMenu &menu, AddressBookV1 &addressBook);
void handleDeleteByName(ConsoleMenu &menu, AddressBookV1 &addressBook);

void handleGetByNameV2(ConsoleMenu &menu, AddressBookV2 &addressBook);
void handleDeleteByNameV2(ConsoleMenu &menu, AddressBookV2 &addressBook);

int main()
{
    std::cout << "Choose AddressBook version (1 or 2): ";
    int version;
    std::cin >> version;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    AddressBookV1 addressBookV1;
    AddressBookV2 addressBookV2;

    if (version == 1) {
        addressBookV1.addContactsFromFile("../ContactsData.txt");
    } else if (version == 2) {
        addressBookV2.addContactsFromFile("../ContactsData.txt");
    } else {
        std::cout << "Invalid version choice. Exiting...\n";
        return 1;
    }

    ConsoleMenu menu = ConsoleMenu();

    bool exit = false;
    while (!exit) {
        menu.drawMenu();
        ConsoleMenu::MenuOption option = menu.getOption();

        switch (option) {
            case ConsoleMenu::MenuOption::GET_FULL_NAME:
                if (version == 1) {
                    handleGetByName(menu, addressBookV1);
                } else if (version == 2) {
                    handleGetByNameV2(menu, addressBookV2);
                }
                break;
            case ConsoleMenu::MenuOption::DELETE_FULL_NAME:
                if (version == 1) {
                    handleDeleteByName(menu, addressBookV1);
                } else if (version == 2) {
                    handleDeleteByNameV2(menu, addressBookV2);
                }
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

void handleGetByNameV2(ConsoleMenu &menu, AddressBookV2 &addressBook)
{
    std::string name = menu.getString();
    std::vector<Contact> contacts = addressBook.queryContacts(name);

    if (contacts.empty()) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    for (Contact contact : contacts){
        menu.printContact(contact);
    }
}

void handleDeleteByNameV2(ConsoleMenu &menu, AddressBookV2 &addressBook)
{
    std::string name = menu.getString();
    addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}