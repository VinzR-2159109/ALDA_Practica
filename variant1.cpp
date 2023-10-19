#include "variant1.h"

#include <iostream>

Variant1::Variant1()
    : m_menu({"get contact information by full name", "delete contact by full name", "Exit program"})
    , m_addressBook(AddressBookV1())
{ }

void Variant1::start()
{
    // load contacts from file
    m_addressBook.addContactsFromFile("../ContactsData.txt");

    // loop until exit
    while (true) {
        m_menu.drawMenu();
        char option = m_menu.getOption();

        switch (option) {
        case '1':
            handleGetByName();
            break;
        case '2':
            handleDeleteByName();
            break;
        case '3':
            return;
        }
    }
}

void Variant1::handleGetByName()
{
    std::string name = m_menu.getString("name");
    const Contact *contact = m_addressBook.getContactByName(name);

    if (contact == nullptr) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    m_menu.printContact(*contact);
}

void Variant1::handleDeleteByName()
{
    std::string name = m_menu.getString("name");
    m_addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}
