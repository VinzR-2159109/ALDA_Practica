#include "consolemenu.h"
#include <iostream>

ConsoleMenu::ConsoleMenu(std::vector<std::string> options)
    : m_options(options)
{}

void ConsoleMenu::drawMenu() const
{
    std::cout << "Addressbook menu - What action would you like to do?\n";

    for (int i = 0; i < m_options.size(); ++i) {
        std::cout << " - (" << i + 1 << ") " << m_options[i] << "\n";
    }
}

char ConsoleMenu::getOption() const
{
    std::cout << "Type the number of the coresponding option: ";

    char answer = std::getchar();
    while (getchar() != '\n');

    if (answer < '1' || answer > '0' + m_options.size()) {
        std::cout << "Error: option " << answer << " is invalid\n\n";
        return getOption();
    }

    std::cout << "\n";

    return answer;
}

std::string ConsoleMenu::getString(const std::string &type) const
{
    std::cout << "Type a " << type << ": ";

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
