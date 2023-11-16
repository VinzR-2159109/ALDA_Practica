#ifndef CONTACT_H
#define CONTACT_H

#include <QString>
#include <QDate>

class Contact
{
public:
    enum class RelationshipStatus { Single, Maried };

    Contact();
    Contact(QString name,
            QString adress,
            QDate dateOfBirth = QDate(),
            RelationshipStatus relationshipStatus = RelationshipStatus::Single);

    QString getName();
    QString getAddress();
    QDate getDateOfBirth();
    RelationshipStatus getRelationShipStatus();

    void setAddress(const QString &newAddress);
    void setDateOfBirth(const QDate &newDateOfBirth);

private:
    QString m_name;
    QString m_address;
    QDate m_dateOfBirth;
    RelationshipStatus m_relationshipStatus;
};

#endif // CONTACT_H
