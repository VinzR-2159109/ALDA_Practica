#ifndef ADDRESSBOOKV3_H
#define ADDRESSBOOKV3_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Contact.h"

class AddressBookV3 {
public:
    void addContact(const Contact &contact);
    void addContacts(const std::vector<Contact> constacts);
    void addContactsFromFile(const std::string &fileName);

    const Contact* getContactByName(const std::string &name) const;
    void deleteContactByName(const std::string &name);

private:
    std::unordered_map<std::string, Contact> contacts;
};

#endif // ADDRESSBOOKV3_H