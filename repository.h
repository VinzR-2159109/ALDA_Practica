#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>
#include "Contact.h"

class Repository
{
public:
    std::vector<Contact> loadContacts(std::string fileName);
};

#endif // REPOSITORY_H
