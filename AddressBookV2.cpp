#include "AddressBookV2.h"
#include "repository.h"

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
    /*
     * Contacts is een unordered_map, hierdoor is verwijderen O(1).
     */

    contacts.erase(name);
}

std::vector<Contact> AddressBookV2::queryContacts(const std::string& query) const
{
    /*
     * Looping over alle contacten in contacts is O(n) in tijdscomplexiteit.
     * Een alternatief is aparte hashmaps voor elke datamember.
     * Dit heeft echter slechtere ruimtecomplexiteit en onderhoudbaarheid door gegevensduplicatie en de noodzaak om bij elke wijziging extra hashmaps aan te maken.
     * Bovendien, wanneer contacten worden verwijderd/toegevoegd, moeten alle hashmaps bewerkt worden.
     *
     * Aangezien de hashmaps de volledige naam als key neemt, kan er eerst gekeken worden in O(1) tijd
     * of deze in de hashmap staat waardoor zoeken op volledige naam sneller gaat.
     */

    std::vector<Contact> result;

    auto it = contacts.find(query);
    if (it != contacts.end()) {
        result.push_back(it->second);
        return result;
    }

    for (const auto& pair : contacts) {
        const Contact& contact = pair.second;

        if (contact.getFirstName() == query ||
            contact.getLastName() == query ||
            contact.getAddress() == query ||
            contact.getPhoneNumber() == query)
        {
            result.push_back(contact);
        }
    }
    return result;
}
