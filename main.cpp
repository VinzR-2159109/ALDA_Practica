#include "productbookwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ProductBookWidget productBook;

    productBook.showMaximized();
    return a.exec();
}
