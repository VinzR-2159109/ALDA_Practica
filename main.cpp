#include <iostream>
#include "AddressBook.h"

int main() {
    // Creating an AddressBook
    AddressBook addressBook;

    // Adding contacts to the address book
    Contact contact1("123 Main St", "555-1234");
    Contact contact2("456 Oak St", "555-5678");

    addressBook.addContact("John Doe", contact1);
    addressBook.addContact("Jane Smith", contact2);

    // Querying information about a contact
    std::string queryName = "John Doe";
    Contact queriedContact = addressBook.findContact(queryName);
    std::cout << "Information about " << queryName << ":\n";
    std::cout << "Address: " << queriedContact.m_address << "\n";
    std::cout << "Phone Number: " << queriedContact.m_phoneNumber << "\n\n";

    // Deleting a contact
    std::string deleteName = "Jane Smith";
    addressBook.deleteContact(deleteName);
    std::cout << deleteName << " has been deleted from the address book.\n\n";

    return 0;
}
