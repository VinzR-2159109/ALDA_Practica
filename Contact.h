#ifndef ALDA_PRACTICUM1_CONTACT_H
#define ALDA_PRACTICUM1_CONTACT_H

#include <string>

class Contact {
public:
    std::string m_address;
    std::string m_phoneNumber;

    Contact(const std::string& address, const std::string& number);
    Contact();
};

#endif //ALDA_PRACTICUM1_CONTACT_H
