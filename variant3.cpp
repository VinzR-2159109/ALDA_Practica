#include "variant3.h"

#include <iostream>

Variant3::Variant3()
    : m_menu({"get contact information by full name", "get contact information by last name", "delete contact by full name", "print all contacts", "Exit program"})
    , m_addressBook(AddressBookV3())
{}

void Variant3::start()
{
    // load contacts from file
    AddressBookV3 addressBook = AddressBookV3();
    addressBook.addContactsFromFile("../ContactsData.txt");

    // loop until exit
    while (true) {
        m_menu.drawMenu();
        char option = m_menu.getOption();

        switch (option) {
        case '1':
            handleGetByFullName();
            break;
        case '2':
            //handleGetByLastName(menu, addressBook);
            break;
        case '3':
            handleDeleteByFullName();
            break;
        case '4':
            //handlePrintAll(menu, addressBook);
            break;
        case '5':
            return;
        }
    }
}

void Variant3::handleGetByFullName()
{
    std::string name = m_menu.getString("name");
    const Contact *contact = m_addressBook.getContactByName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    m_menu.printContact(*contact);
}

void Variant3::handleDeleteByFullName()
{
    std::string name = m_menu.getString("name");
    m_addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}
