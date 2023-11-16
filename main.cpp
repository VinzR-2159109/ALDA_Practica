#include "productbook.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProductBook addressBook;
    addressBook.show();
    return a.exec();
}
