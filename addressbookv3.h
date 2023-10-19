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

    const Contact *getContactByFullName(const std::string &name) const;
    void deleteContactByFullName(const std::string &name);

    const Contact *getContactByLastName(const std::string &name) const;

    std::vector<const Contact*> getContactsSorted() const;
private:
    std::unordered_map<std::string, Contact> m_contacts;
    std::vector<const Contact*> radixSort() const;
};

#endif // ADDRESSBOOKV3_H
