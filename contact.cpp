#include "contact.h"

Contact::Contact() : m_name(), m_address(""), m_dateOfBirth(QDate()), m_relationshipStatus(RelationshipStatus::Single)
{ }

Contact::Contact(QString name, QString address, QDate dateOfBirth, RelationshipStatus relationshipStatus)
    : m_name(name), m_address(address), m_dateOfBirth(dateOfBirth), m_relationshipStatus(relationshipStatus)
{ }

// getters
QString Contact::getName()
{
    return m_name;
}

QString Contact::getAddress()
{
    return m_address;
}

QDate Contact::getDateOfBirth()
{
    return m_dateOfBirth;
}

Contact::RelationshipStatus Contact::getRelationShipStatus()
{
    return m_relationshipStatus;
}

void Contact::setAddress(const QString &newAddress)
{
    m_address = newAddress;
}

void Contact::setDateOfBirth(const QDate &newDateOfBirth)
{
    m_dateOfBirth = newDateOfBirth;
}
