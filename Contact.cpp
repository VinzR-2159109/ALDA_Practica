#include "Contact.h"

Contact::Contact(const std::string& address, const std::string& phoneNumber) : m_address(address), m_phoneNumber(phoneNumber) {}

Contact::Contact() : m_address(""), m_phoneNumber("") {}

