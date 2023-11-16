#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H

#include "qwidget.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>

#include "finddialog.h"
#include "contact.h"

class AddressBook : public QWidget
{
    Q_OBJECT

public:
    AddressBook(QWidget *parent = nullptr);

public slots:
    void addContact();
    void submitContact();
    void cancel();
    void next();
    void previous();
    void editContact();
    void removeContact();
    void findContact();

private:
    enum Mode { NavigationMode, AddingMode, EditingMode };

    QPushButton *addButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;
    QPushButton *nextButton;
    QPushButton *previousButton;
    QPushButton *editButton;
    QPushButton *removeButton;
    QPushButton *findButton;

    QLineEdit *nameLine;
    QTextEdit *addressText;
    QDateEdit *dateOfBirthText;

    QMap<QString, Contact> contacts;
    QString oldName;
    QString oldAddress;
    QDate oldDateOfBirth;
    Mode currentMode;
    FindDialog *dialog;

    void updateInterface(Mode mode);
};

#endif // ADDRESSBOOK_H
