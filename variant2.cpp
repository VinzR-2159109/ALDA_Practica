#include <iostream>
#include "variant2.h"

void variant2::start()
{
    m_addressBook.addContactsFromFile("../ContactsData.txt");

    while (true) {
        m_menu.drawMenu();
        char option = m_menu.getOption();

        switch (option) {
            case '1':
                handeleGetByQuery();
                break;
            case '2':
                handleDeleteByName();
                break;
            case '3':
                return;
        }
    }
}

void variant2::handeleGetByQuery()
{
    std::string query = m_menu.getString("query");
    std::vector<Contact> contacts = m_addressBook.queryContacts(query);

    if (contacts.empty()) {
        std::cout << "Error: Contact not found!\n\n";
        return;
    }

    for (const Contact& contact : contacts){
        m_menu.printContact(contact);
    }
}

void variant2::handleDeleteByName()
{
    std::string name = m_menu.getString("name");
    m_addressBook.deleteContactByName(name);

    std::cout << name << " has been deleted\n\n";
}
