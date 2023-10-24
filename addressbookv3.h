#ifndef ADDRESSBOOKV3_H
#define ADDRESSBOOKV3_H

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include "Contact.h"

class AddressBookV3 {
public:
    void addContact(const Contact &contact);
    void addContacts(const std::vector<Contact> constacts);
    void addContactsFromFile(const std::string &fileName);

    const Contact * getContactByFullName(const std::string &name) const;
    void deleteContactByFullName(const std::string &name);

    std::vector<const Contact*> getContactsByLastName(const std::string &name) const;

    std::vector<const Contact*> getContactsSorted() const;
private:
    std::multimap<std::string, Contact> m_contacts;
};

#endif // ADDRESSBOOKV3_H
