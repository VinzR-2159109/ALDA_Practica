#include "consolemenu.h"
#include <iostream>

void ConsoleMenu::drawMenu() const
{
    std::cout << "Adress Menu - What action would you like to do?\n";
    std::cout << " - (1) get contact information by full name.\n";
    std::cout << " - (2) delete contact by full name.\n";
    std::cout << " - (3) Exit program.\n";
}

ConsoleMenu::MenuOption ConsoleMenu::getOption() const
{
    std::cout << "Type the number of the coresponding option: ";

    char answer = std::getchar();
    while ((getchar()) != '\n')
        ;

    MenuOption menuOption = static_cast<MenuOption>(answer);

    if (answer < '1' || answer > '3') {
        std::cout << "Error: option " << answer << " is invalid\n\n";
        return getOption();
    }

    return menuOption;
}

std::string ConsoleMenu::getString() const
{
    std::cout << "Type a name: ";

    std::string line;
    std::getline(std::cin, line);

    return line;
}

void ConsoleMenu::printContact(const Contact &constact) const
{
    std::cout << "\n"
              << "------------------------------------" << "\n"
              << "Name: " << constact.getFullName()     << "\n"
              << "Address: " << constact.getAddress()   << "\n"
              << "Phone: " << constact.getPhoneNumber() << "\n"
              << "------------------------------------" << "\n\n";
}
