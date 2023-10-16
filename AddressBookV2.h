//
// Created by vinzr on 16/10/2023.
//

#ifndef ALDA_PRACTICUM1_ADDRESSBOOKV2_H
#define ALDA_PRACTICUM1_ADDRESSBOOKV2_H


#include <vector>
#include <unordered_map>
#include "Contact.h"

class AddressBookV2 {
public:
    void addContact(const Contact &contact);
    void addContacts(const std::vector<Contact> contacts);
    void addContactsFromFile(const std::string &fileName);
    void deleteContactByName(const std::string &name);
    std::vector<Contact> queryContacts(const std::string &query) const;

private:
    std::unordered_map<std::string, Contact> contacts;
};


#endif //ALDA_PRACTICUM1_ADDRESSBOOKV2_H
