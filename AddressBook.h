#ifndef ALDA_PRACTICUM1_ADDRESSBOOK_H
#define ALDA_PRACTICUM1_ADDRESSBOOK_H

#include <unordered_map>
#include <string>
#include "Contact.h"

class AddressBook {
public:
    void addContact(const std::string &name, const Contact &contact);
    Contact findContact(const std::string &name) const;
    void deleteContact(const std::string &name);

private:
    std::unordered_map<std::string, Contact> contacts;
};
#endif //ALDA_PRACTICUM1_ADDRESSBOOK_H
