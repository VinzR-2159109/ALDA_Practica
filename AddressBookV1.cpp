#include "AddressBookV1.h"
#include "repository.h"

void AddressBookV1::addContact(const Contact &contact)
{
    contacts[contact.getFullName()] = contact;
}

void AddressBookV1::addContacts(const std::vector<Contact> constacts)
{
    for (const Contact &contact : constacts) {
        addContact(contact);
    }
}

void AddressBookV1::addContactsFromFile(const std::string& fileName)
{
    std::vector<Contact> contacts = dataRepository().loadContacts(fileName);
    addContacts(contacts);
}

const Contact* AddressBookV1::getContactByName(const std::string& name) const
{
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        return &it->second;
    }

    return nullptr;
}

void AddressBookV1::deleteContactByName(const std::string& name)
{
    contacts.erase(name);
}
