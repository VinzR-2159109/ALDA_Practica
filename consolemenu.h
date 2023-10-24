#ifndef CONSOLEMENU_H
#define CONSOLEMENU_H

#include <string>
#include <vector>
#include "Contact.h"

class ConsoleMenu
{
public:
    ConsoleMenu(std::vector<std::string> options);

    void drawMenu() const;
    char getOption() const;
    std::string getString(const std::string &type) const;

    void printContact(const Contact &constact) const;
    void printContacts(std::vector<const Contact*> contacts);

private:
    std::vector<std::string> m_options;
};

#endif // CONSOLEMENU_H
