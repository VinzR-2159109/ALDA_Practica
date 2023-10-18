#ifndef VARIANT3_H
#define VARIANT3_H

#include "consolemenu.h"
#include "addressbookv3.h"

class Variant3
{
public:
    Variant3();

    void start();

private:
    ConsoleMenu m_menu;
    AddressBookV3 m_addressBook;

    void handleGetByFullName();
    void handleDeleteByFullName();
    void handleGetByLastName();
    void handlePrintAll();
};

#endif // VARIANT3_H
