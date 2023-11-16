#ifndef PRODUCTBOOK_H
#define PRODUCTBOOK_H

#include "producttrie.h"
#include "qwidget.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>

#include <QListWidget>

class ProductBook : public QWidget
{
    Q_OBJECT

public:
    ProductBook(QWidget *parent = nullptr);

public slots:
    void addProduct();
    void findProduct();

private:
    enum Mode { NavigationMode, AddingMode, EditingMode };

    ProductTrie m_productTrie;

    QPushButton *m_addButton;

    QLineEdit *m_searchLine;
    QListWidget *m_resultsList;

    Mode m_currentMode;

    void updateInterface(Mode mode);
};

#endif // PRODUCTBOOK_H
