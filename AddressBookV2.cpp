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

/*
 * Contacts is een unordered_map, hierdoor is verwijderen ook O(1).
 */
void AddressBookV2::deleteContactByName(const std::string& name)
{
    contacts.erase(name);
}
/*
 * Looping over alle contacten in contacts is O(n) in tijdscomplexiteit.
 * Een alternatief is aparte hashmaps voor elke datamember.
 * Dit heeft echter slechtere ruimtecomplexiteit en onderhoudbaarheid door gegevensduplicatie en de noodzaak om bij elke wijziging extra hashmaps aan te maken.
 * Bovendien, wanneer contacten worden verwijderd/toegevoegd, moeten alle hashmaps bewerkt worden.
 */
std::vector<Contact> AddressBookV2::queryContacts(const std::string& query) const
{
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
    return result;
}