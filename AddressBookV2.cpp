#include "AddressBookV2.h"
#include "repository.h"
#include <iostream>
#include <chrono>

void AddressBookV2::addContact(const Contact &contact)
{
    contacts[contact.getFullName()] = contact;
}

void AddressBookV2::addContacts(const std::vector<Contact> contacts)
{
    for (const Contact &contact : contacts) {
        addContact(contact);
    }
}

void AddressBookV2::addContactsFromFile(const std::string& fileName)
{
    std::vector<Contact> contacts = Repository().loadContacts(fileName);
    addContacts(contacts);
}

void AddressBookV2::deleteContactByName(const std::string& name)
{
    contacts.erase(name);
}

std::vector<Contact> AddressBookV2::queryContacts(const std::string& query) const
{
    //auto start_time = std::chrono::high_resolution_clock::now();

    std::vector<Contact> result;
    for (const auto& pair : contacts) {
        const Contact& contact = pair.second;

        if (contact.getFirstName() == query ||
            contact.getLastName() == query ||
            contact.getFullName() == query ||
            contact.getAddress() == query ||
            contact.getPhoneNumber() == query)
        {
            result.push_back(contact);
        }
    }
    /*
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time).count();
    std::cout << "Query duurde " << duration << " milliseconden." << std::endl;
     */

    return result;
}