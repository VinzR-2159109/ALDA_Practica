#ifndef VARIANT1_H
#define VARIANT1_H

#include "consolemenu.h"
#include "AddressBookV1.h"

class Variant1
{
public:
    Variant1();

    void start();

private:
    ConsoleMenu m_menu;
    AddressBookV1 m_addressBook;

    void handleGetByName();
    void handleDeleteByName();
};

#endif // VARIANT1_H
