#ifndef ALDA_PRACTICUM1_CONTACT_H
#define ALDA_PRACTICUM1_CONTACT_H

#include <string>

class Contact {
public:
    Contact();
    Contact(const std::string &firstName, const std::string &lastName, const std::string &address, const std::string &phonenumber);

    std::string getFullName() const;
    std::string getFirstName() const;
    std::string getLastName() const;

    std::string getAddress() const;
    void setAddress(const std::string &newAddress);

    std::string getPhoneNumber() const;
    void setPhoneNumber(const std::string &newPhoneNumber);

private:
    std::string m_firstName;
    std::string m_lastName;
    std::string m_address;
    std::string m_phoneNumber;
};

#endif //ALDA_PRACTICUM1_CONTACT_H
