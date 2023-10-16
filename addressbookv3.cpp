#include "addressbookv3.h"
#include "repository.h"

void AddressBookV3::addContact(const Contact &contact)
{
    contacts[contact.getFullName()] = contact;
}

void AddressBookV3::addContacts(const std::vector<Contact> constacts)
{
    for (const Contact &contact : constacts) {
        addContact(contact);
    }
}

void AddressBookV3::addContactsFromFile(const std::string& fileName)
{
    std::vector<Contact> contacts = Repository().loadContacts(fileName);
    addContacts(contacts);
}

const Contact* AddressBookV3::getContactByName(const std::string& name) const
{
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        return &it->second;
    }

    return nullptr;
}

void AddressBookV3::deleteContactByName(const std::string& name)
{
    contacts.erase(name);
}
