#include "productbook.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

ProductBook::ProductBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    m_nameLine = new QLineEdit;

    // create buttons
    m_addButton = new QPushButton(tr("&test"));
    m_addButton->show();

    // connect clicked events to correct method
    connect(m_addButton, &QPushButton::clicked, this, &ProductBook::addProduct);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(m_addButton, Qt::AlignTop);
    buttonLayout1->addStretch();

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(nameLabel, 0, 0);
    mainLayout->addWidget(m_nameLine, 0, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));

    updateInterface(NavigationMode);

    addProduct();
}

void ProductBook::addProduct()
{
    {
        Product *p = new Product("a", "", "", "", 0, 0, 0, 0, 0, false);
        m_productTrie.insert(p);
    }

    {
        Product *p = new Product("b", "", "", "", 0, 0, 0, 0, 0, false);
        m_productTrie.insert(p);
    }

    {
        Product *p = new Product("aa", "", "", "", 0, 0, 0, 0, 0, false);
        m_productTrie.insert(p);
    }

    {
        Product *p = new Product("aba", "", "", "", 0, 0, 0, 0, 0, false);
        m_productTrie.insert(p);
    }
}

void ProductBook::findProduct()
{

}

void ProductBook::updateInterface(Mode mode)
{

}
