#include "Contact.h"

Contact::Contact()
    : Contact("", "", "", "")
{}

Contact::Contact(const std::string &firstName, const std::string &lastName, const std::string &address, const std::string &phonenumber)
    : m_firstName(firstName)
    , m_lastName(lastName)
    , m_address(address)
    , m_phoneNumber(phonenumber)
{}

std::string Contact::getFullName() const
{
    return m_firstName + " " + m_lastName;
}

std::string Contact::getFirstName() const
{
    return m_firstName;
}

std::string Contact::getLastName() const
{
    return m_lastName;
}

std::string Contact::getAddress() const
{
    return m_address;
}

void Contact::setAddress(const std::string &newAddress)
{
    m_address = newAddress;
}

std::string Contact::getPhoneNumber() const
{
    return m_phoneNumber;
}

void Contact::setPhoneNumber(const std::string &newPhoneNumber)
{
    m_phoneNumber = newPhoneNumber;
}
