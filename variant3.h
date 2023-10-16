#ifndef VARIANT3_H
#define VARIANT3_H

#include "consolemenu.h"
#include "addressbookv3.h"

class Variant3
{
public:
    void start();

private:
    void handleGetByName(ConsoleMenu &menu, AddressBookV3 &addressBook);
    void handleDeleteByName(ConsoleMenu &menu, AddressBookV3 &addressBook);
};

#endif // VARIANT3_H
