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
    std::vector<Contact> contacts = Repository().loadContacts(fileName);
    addContacts(contacts);
}

const Contact* AddressBookV1::getContactByFullName(const std::string& name) const
{
    /*
     * Contacts is een unordered_map.
     * Key = "Full Name" en Value = contact, hierdoor is zoeken in deze map O(1).
     */

    auto it = contacts.find(name);
    if (it != contacts.end()) {
        return &it->second;
    }

    return nullptr;
}

void AddressBookV1::deleteContactByFullName(const std::string& name)
{
    /*
     * Contacts is een unordered_map, hierdoor is verwijderen O(1).
     */

    contacts.erase(name);
}
