#include "addressbook.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;

    QLabel *addressLabel = new QLabel(tr("Address:"));
    addressText = new QTextEdit;

    QLabel *dateOfBirthLabel = new QLabel(tr("Date of Birth"));
    dateOfBirthText = new QDateEdit;

    // create buttons
    addButton = new QPushButton(tr("&Add"));
    addButton->show();
    submitButton = new QPushButton(tr("&Submit"));
    submitButton->hide();
    cancelButton = new QPushButton(tr("&Cancel"));
    cancelButton->hide();
    editButton = new QPushButton(tr("&Edit"));
    editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
    removeButton->setEnabled(false);
    nextButton = new QPushButton(tr("&Next"));
    nextButton->setEnabled(false);
    previousButton = new QPushButton(tr("&Previous"));
    previousButton->setEnabled(false);
    findButton = new QPushButton(tr("&Find"));
    findButton->setEnabled(false);

    // create find dialog
    dialog = new FindDialog(this);

    // connect clicked events to correct method
    connect(addButton, &QPushButton::clicked, this, &AddressBook::addContact);
    connect(submitButton, &QPushButton::clicked, this, &AddressBook::submitContact);
    connect(cancelButton, &QPushButton::clicked, this, &AddressBook::cancel);
    connect(editButton, &QPushButton::clicked, this, &AddressBook::editContact);
    connect(removeButton, &QPushButton::clicked, this, &AddressBook::removeContact);
    connect(nextButton, &QPushButton::clicked, this, &AddressBook::next);
    connect(previousButton, &QPushButton::clicked, this, &AddressBook::previous);
    connect(findButton, &QPushButton::clicked, this, &AddressBook::findContact);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(addButton, Qt::AlignTop);
    buttonLayout1->addWidget(submitButton);
    buttonLayout1->addWidget(cancelButton);
    buttonLayout1->addWidget(editButton);
    buttonLayout1->addWidget(removeButton);
    buttonLayout1->addStretch();

    // create navigation buttons layout
    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
    buttonLayout2->addWidget(previousButton);
    buttonLayout2->addWidget(nextButton);
    buttonLayout2->addWidget(findButton);

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);
    mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(addressText, 1, 1);
    mainLayout->addWidget(dateOfBirthLabel, 2, 0);
    mainLayout->addWidget(dateOfBirthText, 2, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addLayout(buttonLayout2, 3, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));

    updateInterface(NavigationMode);
}

void AddressBook::addContact()
{
    // store information from input fields
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    oldDateOfBirth = dateOfBirthText->date();

    // clear the input fields
    nameLine->clear();
    addressText->clear();
    dateOfBirthText->clear();

    updateInterface(AddingMode);
}

void AddressBook::submitContact()
{
    // get information from input fields
    QString name = nameLine->text();
    QString address = addressText->toPlainText();
    QDate dateOfBirth = dateOfBirthText->date();

    // check if valid
    if (name.isEmpty() || address.isEmpty()) {
        QMessageBox::information(this, tr("Empty Field"), tr("Please enter a name and address."));
        return;
    }


    if (currentMode == AddingMode) {
        // check if contact does not exists -> else error
        if (!contacts.contains(name)) {
            Contact newContact(name, address, dateOfBirth);
            contacts.insert(name, newContact);

            QMessageBox::information(this,
                                     tr("Add Successful"),
                                     tr("\"%1\" has been added to your address book.").arg(name));
        } else {
            QMessageBox::information(this,
                                     tr("Add Unsuccessful"),
                                     tr("Sorry, \"%1\" is already in your address book.").arg(name));
            return;
        }
    } else if (currentMode == EditingMode) {
        if (oldName != name) {
            if (!contacts.contains(name)) {
                QMessageBox::information(this,
                                         tr("Edit Successful"),
                                         tr("\"%1\" has been edited in your address book.")
                                             .arg(oldName));
                contacts.remove(oldName);
                Contact newContact(name, address, dateOfBirth);
                contacts.insert(name, newContact);
            } else {
                QMessageBox::information(this,
                                         tr("Edit Unsuccessful"),
                                         tr("Sorry, \"%1\" is already in your address book.")
                                             .arg(name));
            }
        } else if (oldAddress != address) {
            QMessageBox::information(this,
                                     tr("Edit Successful"),
                                     tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name].setAddress(address);
        } else if (oldDateOfBirth != dateOfBirth) {
            QMessageBox::information(this,
                                     tr("Edit Successful"),
                                     tr("\"%1\" has been edited in your address book.").arg(name));
            contacts[name].setDateOfBirth(dateOfBirth);
        }
    }

    // reset UI
    updateInterface(NavigationMode);
}

void AddressBook::cancel()
{
    // reset input fields to stored values
    nameLine->setText(oldName);

    addressText->setText(oldAddress);

    dateOfBirthText->setDate(oldDateOfBirth);

    updateInterface(NavigationMode);
}

void AddressBook::next()
{
    // if iterator is at end, go to start

    QString name = nameLine->text();
    auto it = contacts.find(name);

    if (it != contacts.end())
        it++;

    if (it == contacts.end())
        it = contacts.begin();

    nameLine->setText(it.key());
    addressText->setText(it.value().getAddress());
    dateOfBirthText->setDate(it.value().getDateOfBirth());
}

void AddressBook::previous()
{
    // if iterator is at start, go to end

    QString name = nameLine->text();
    auto it = contacts.find(name);

    if (it == contacts.end()) {
        nameLine->clear();
        addressText->clear();
        dateOfBirthText->clear();
        return;
    }

    if (it == contacts.begin())
        it = contacts.end();

    it--;
    nameLine->setText(it.key());
    addressText->setText(it.value().getAddress());
    dateOfBirthText->setDate(it.value().getDateOfBirth());
}

void AddressBook::editContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();
    oldDateOfBirth = dateOfBirthText->date();

    updateInterface(EditingMode);
}

void AddressBook::removeContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (contacts.contains(name)) {
        int button = QMessageBox::question(this,
                                           tr("Confirm Remove"),
                                           tr("Are you sure you want to remove \"%1\"?").arg(name),
                                           QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {
            previous();
            contacts.remove(name);

            QMessageBox::information(this,
                                     tr("Remove Successful"),
                                     tr("\"%1\" has been removed from your address book.").arg(name));
        }
    }

    updateInterface(NavigationMode);
}

void AddressBook::updateInterface(Mode mode)
{
    currentMode = mode;

    switch (currentMode) {
    case AddingMode:
    case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);
        dateOfBirthText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);
        findButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();
        break;
    case NavigationMode:

        if (contacts.isEmpty()) {
            nameLine->clear();
            addressText->clear();
        }

        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        dateOfBirthText->setReadOnly(true);

        addButton->setEnabled(true);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number > 1);
        findButton->setEnabled(true);

        submitButton->hide();
        cancelButton->hide();
        break;
    }
}

void AddressBook::findContact()
{
    dialog->show();

    if (dialog->exec() == QDialog::Accepted) {
        QString contactName = dialog->getFindText();

        if (contacts.contains(contactName)) {
            nameLine->setText(contactName);
            addressText->setText(contacts.value(contactName).getAddress());
            dateOfBirthText->setDate(contacts.value(contactName).getDateOfBirth());
        } else {
            QMessageBox::information(this,
                                     tr("Contact Not Found"),
                                     tr("Sorry, \"%1\" is not in your address book.")
                                         .arg(contactName));
            return;
        }
    }

    updateInterface(NavigationMode);
}
