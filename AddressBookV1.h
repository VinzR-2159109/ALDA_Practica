#ifndef ADDRESSBOOKV1_H
#define ADDRESSBOOKV1_H

#include <unordered_map>
#include <vector>
#include <string>
#include "Contact.h"

class AddressBookV1 {
public:
    void addContact(const Contact &contact);
    void addContacts(const std::vector<Contact> constacts);
    void addContactsFromFile(const std::string &fileName);
    
    const Contact* getContactByFullName(const std::string &name) const;
    void deleteContactByFullName(const std::string &name);

private:
    std::unordered_map<std::string, Contact> contacts;
};

#endif //ADDRESSBOOKV1_H
