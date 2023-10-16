#ifndef VARIANT1_H
#define VARIANT1_H

#include "consolemenu.h"
#include "AddressBookV1.h"

class Variant1
{
public:
    void start();

private:
    void handleGetByName(ConsoleMenu &menu, AddressBookV1 &addressBook);
    void handleDeleteByName(ConsoleMenu &menu, AddressBookV1 &addressBook);
};

#endif // VARIANT1_H
