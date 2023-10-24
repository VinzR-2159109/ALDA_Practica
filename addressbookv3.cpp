#include "addressbookv3.h"
#include "repository.h"

void AddressBookV3::addContact(const Contact &contact)
{
    m_contacts.insert(std::make_pair(contact.getLastName(), contact));
}

void AddressBookV3::addContacts(const std::vector<Contact> constacts)
{
    for (const Contact &contact : constacts) {
        addContact(contact);
    }
}

void AddressBookV3::addContactsFromFile(const std::string &fileName)
{
    std::vector<Contact> contacts = Repository().loadContacts(fileName);
    addContacts(contacts);
}

const Contact *AddressBookV3::getContactByFullName(const std::string &name) const
{
    /**
     * De contacten worden bijgehouden in een multimap waarvan de keys de achternamen zijn.
     * In een multimap kunnen we zoeken op een key in O(log(n)) tijd. Hierna moeten we over
     * alle waardes die bij de key horen itereren, dit is O(k).
     * De totale tijdscomplexiteit is dus O(log(n) + k).
     *
     * Het zoeken in een unordered multimap heeft een tijdscomplexiteit van O(1).
     * Hierdoor wordt de tijdscomplexiteit O(1 + k)
     * Dit zou een verbetering zijn voor deze functie, maar een (gesorteerde) multimap
     * geeft veel voordelen bij de functie getContactsSorted().
     *
     * Een andere mogelijkheid is om een apparte unordered_map bij te houden met de volledige naam als key.
     * Dit zou er voor zorgen dat de tijdscomplexiteit O(1) wordt, maar hierdoor heb je een extra datastructuur nodig
     * waardoor je op 2 plaatsten moet toevoegen en verwijderen.
     */

    int startLastNameIndex = name.find(' ') + 1;
    std::string lastName = name.substr(startLastNameIndex);

    auto range = m_contacts.equal_range(lastName);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.getFullName() == name) {
            return &it->second;
        }
    }

    return nullptr;
}

void AddressBookV3::deleteContactByFullName(const std::string &name)
{
    /**
     * De contacten worden bijgehouden in een multimap waarvan de keys de achternamen zijn.
     * In een multimap kunnen we zoeken op een key in O(log(n)) tijd. Hierna moeten we over
     * alle waardes die bij de key horen itereren, dit is O(k).
     * De totale tijdscomplexiteit is dus O(log(n) + k).
     *
     * Het zoeken in een unordered multimap heeft een tijdscomplexiteit van O(1).
     * Hierdoor wordt de tijdscomplexiteit O(1 + k)
     * Dit zou een verbetering zijn voor deze functie, maar een (gesorteerde) multimap
     * geeft veel voordelen bij de functie getContactsSorted().
     *
     * Een andere mogelijkheid is om een apparte unordered_map bij te houden met de volledige naam als key.
     * Dit zou er voor zorgen dat de tijdscomplexiteit O(1) wordt, maar hierdoor heb je een extra datastructuur nodig
     * waardoor je op 2 plaatsten moet toevoegen en verwijderen.
     */

    int startLastNameIndex = name.find(' ') + 1;
    std::string lastName = name.substr(startLastNameIndex);

    auto range = m_contacts.equal_range(lastName);
    for (auto it = range.first; it != range.second; ++it) {
        if (it->second.getFullName() == name) {
            m_contacts.erase(it);
            return;
        }
    }
}

std::vector<const Contact*> AddressBookV3::getContactsByLastName(const std::string &name) const
{
    /**
     * De contacten worden bijgehouden in een multimap waarvan de keys de achternamen zijn.
     * In een multimap kunnen we zoeken op een key in O(log(n)) tijd. Hierna moeten we over
     * alle waardes die bij de key horen itereren, dit is O(k).
     * De totale tijdscomplexiteit is dus O(log(n) + k).
     *
     * Het zoeken in een unordered multimap heeft een tijdscomplexiteit van O(1).
     * Dit zou een verbetering zijn voor deze functie, maar een (gesorteerde) multimap
     * geeft veel voordelen bij de functie getContactsSorted().
     */

    int count = m_contacts.count(name);

    if (count == 0)
        return std::vector<const Contact*>();

    std::vector<const Contact*> foundContacts(count);

    auto it = m_contacts.find(name);
    for (int i = 0; i < count; ++i) {
        foundContacts[i] = &it->second;
        it++;
    }

    return foundContacts;
}

std::vector<const Contact*> AddressBookV3::getContactsSorted() const
{
    /**
     * De volgende opties zijn bekeken:
     *  - std::sort functie
     *  - Radix sort algoritme
     *  - een (gesorteerde) multimap
     *
     * De std::sort functie heeft een complexiteit van O(n log(n))
     * en runt in 815061 µs op de geteste pc
     *
     * Het radix sort algoritme heeft een tijd complexiteit van O(n * k)
     * en runt in 578724 µs op de geteste pc
     *  - n = het aantal strings in de array
     *  - k = het aantal karakters van de langste string in deze array
     * Aangezien n >>> k kan k verwaarloosd worden waadoor het algoritme O(n) wordt.
     * Het nadeel van deze implementatie is dat enkel karakters van a - z gebruikt kunnen worden
     * en dat er een 2de lijst nodig is waaroor er dubbel zo veel geheugen verbruikt wordt.
     *
     * Een multimap kan voor elke key meerdere values bijhouden. Dit is nodig omdat meerdere contacten
     * dezelfde achternaam kunnen hebben. Aangezien een multimap de data op een gesorteerde manier bijhoudt
     * kunnen de contacten in een vector omgezet worden door over de multimap te itereren.
     * Dit is O(n), maar runt in 199685 µs. Dit is ongeveer 3x sneller dan het radix sort algoritme.
     */

    std::vector<const Contact *> sortedContacts(m_contacts.size());

    int counter = 0;
    for (auto it = m_contacts.begin(); it != m_contacts.end(); it++) {
        sortedContacts[counter] = &it->second;
        counter++;
    }

    return sortedContacts;
}
