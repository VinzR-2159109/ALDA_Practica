#include "variant3.h"

#include <iostream>

Variant3::Variant3()
    : m_menu({"get contact information by full name",
              "get contact information by last name",
              "delete contact by full name",
              "print all contacts",
              "Exit program"})
    , m_addressBook(AddressBookV3())
{}

void Variant3::start()
{
    // load contacts from file
    m_addressBook.addContactsFromFile("ContactsData.txt");

    // loop until exit
    while (true) {
        m_menu.drawMenu();
        char option = m_menu.getOption();

        switch (option) {
        case '1':
            handleGetByFullName();
            break;
        case '2':
            handleGetByLastName();
            break;
        case '3':
            handleDeleteByFullName();
            break;
        case '4':
            handlePrintAll();
            break;
        case '5':
            return;
        }
    }
}

void Variant3::handleGetByFullName()
{
    std::string name = m_menu.getString("name");
    const Contact *contact = m_addressBook.getContactByFullName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    m_menu.printContact(*contact);
}

void Variant3::handleDeleteByFullName()
{
    std::string name = m_menu.getString("name");
    m_addressBook.deleteContactByFullName(name);

    std::cout << name << " has been deleted\n\n";
}

void Variant3::handleGetByLastName()
{
    // code ...
}

void Variant3::handlePrintAll()
{
    std::vector<const Contact *> sortedContacts = m_addressBook.getContactsSorted();
    for (const Contact *contact : sortedContacts) {
        m_menu.printContact(*contact);
    }
}
