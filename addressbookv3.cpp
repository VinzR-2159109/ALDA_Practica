#include "addressbookv3.h"
#include "repository.h"

#include <chrono>
#include <algorithm>
#include <iostream>

void AddressBookV3::addContact(const Contact &contact)
{
    m_contacts[contact.getFullName()] = contact;
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
    auto it = m_contacts.find(name);
    if (it != m_contacts.end()) {
        return &it->second;
    }

    return nullptr;
}

void AddressBookV3::deleteContactByFullName(const std::string &name)
{
    m_contacts.erase(name);
}

const Contact *AddressBookV3::getContactByLastName(const std::string &name) const
{
    // code ...

    return nullptr;
}

std::vector<const Contact *> AddressBookV3::getContactsSorted() const
{
    std::vector<const Contact *> sortedContacts = radixSort();
    return sortedContacts;
}

std::vector<const Contact *> AddressBookV3::radixSort() const
{
    /**
     * Radix sort heeft een tijd complexiteit van O(n * k) (578724 µs)
     * met n het aantal strings in de array en k het aantal karakters van de langste string in deze array.
     * Aangezien n >>> k kan k verwaarloosd worden waadoor het algoritme O(n) wordt.
     *
     * Het nadeel van deze implementatie is dat enkel karakters van a - z gebruikt kunnen worden.
     *
     * De std::sort functie heeft een complexiteit van O(n log(n)) (815061 µs)
     */

    std::vector<const Contact *> contacts(m_contacts.size());

    // get max string length and copy contacts to vector
    int maxStringLength = 0;
    int counter = 0;
    auto it = m_contacts.begin();
    for (auto &it : m_contacts) {
        int length = it.second.getLastName().length();
        if (length > maxStringLength)
            maxStringLength = length;

        contacts[counter] = &it.second;
        counter++;
    }

    int size = contacts.size();
    for (int place = maxStringLength - 1; place >= 0; place--) {
        std::vector<const Contact *> sortedContacts(size);
        int count[26] = {0};

        // Count the occurrences of each character at the given place
        for (int i = 0; i < size; i++) {
            std::string name = contacts[i]->getLastName();

            int index;
            if (place >= name.length()) {
                index = 0;
            } else {
                index = std::tolower(name[place]) - 'a';
            }

            count[index]++;
        }

        // Calculate the cumulative count
        for (int i = 1; i < 26; i++) {
            count[i] = count[i] + count[i - 1];
        }

        // Build the sorted array -> from end to front to make it a stable algorithm
        for (int i = size - 1; i >= 0; i--) {
            std::string name = contacts[i]->getLastName();

            int index;
            if (place >= name.length()) {
                index = 0;
            }
            else {
                index = std::tolower(name[place]) - 'a';
            }

            sortedContacts[count[index]-- - 1] = contacts[i];
        }

        // Copy the sorted array back into the original array
        for (int i = 0; i < size; i++) {
            contacts[i] = sortedContacts[i];
        }
    }

    return contacts;
}
