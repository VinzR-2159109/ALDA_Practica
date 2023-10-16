#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include <string>
#include "Contact.h"

class ConsoleMenu
{
public:
    enum class MenuOption { GET_FULL_NAME = '1', DELETE_FULL_NAME = '2', EXIT = '3'};

    void drawMenu() const;
    MenuOption getOption() const;
    std::string getString() const;

    void printContact(const Contact &constact) const;
};

#endif // CONSOLEMENU_H
