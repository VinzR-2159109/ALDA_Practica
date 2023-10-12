#include "AddressBook.h"
#include <stdexcept>

void AddressBook::addContact(const std::string& name, const Contact& contact) {
    contacts[name] = contact;
}

Contact AddressBook::findContact(const std::string& name) const {
    auto it = contacts.find(name);
    if (it != contacts.end()) {
        return it->second;
    }
    throw std::invalid_argument("Contact not found: " + name);
}

void AddressBook::deleteContact(const std::string& name) {contacts.erase(name);}
