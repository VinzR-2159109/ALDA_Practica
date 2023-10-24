#include <iostream>

#include "consolemenu.h"
#include "variant1.h"
#include "variant2.h"
#include "variant3.h"


int main()
{
    char option = '0';
    {
        std::vector<std::string> menuOptions = {"Start variant 1", "Start variant 2", "Start variant 3"};
        ConsoleMenu menu = ConsoleMenu(menuOptions);

        menu.drawMenu();
        option = menu.getOption();
    }

    switch (option) {
    case '1':
        Variant1().start();
        break;
    case '2':
        variant2().start();
        break;
    case '3':
        Variant3().start();
        break;
    }

    return 0;
}

