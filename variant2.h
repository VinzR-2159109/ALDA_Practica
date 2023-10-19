#ifndef ALDA_PRACTICUM1_VARIANT2_H
#define ALDA_PRACTICUM1_VARIANT2_H

#include "consolemenu.h"
#include "AddressBookV2.h"

class variant2 {
    public:
        variant2();
        void start();

    private:
        ConsoleMenu m_menu;
        AddressBookV2 m_addressBook;

        void handeleGetByQuery();
        void handleDeleteByName();
    };

#endif //ALDA_PRACTICUM1_VARIANT2_H
