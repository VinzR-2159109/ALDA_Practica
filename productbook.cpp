#include "productbook.h"
#include "repository.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

ProductBook::ProductBook(QWidget *parent)
    : QWidget(parent)
{
    // create search label
    QLabel *searchLabel = new QLabel(tr("Name:"));
    m_searchLine = new QLineEdit;

    // create result list
    QLabel *resultLabel = new QLabel(tr("results:"));
    m_resultsList = new QListWidget();

    // create buttons
    m_addButton = new QPushButton(tr("&search"));
    m_addButton->show();

    // connect clicked events to correct method
    connect(m_addButton, &QPushButton::clicked, this, &ProductBook::findProduct);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(m_addButton, Qt::AlignTop);
    buttonLayout1->addStretch();

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(searchLabel, 0, 0);
    mainLayout->addWidget(m_searchLine, 0, 1);
    mainLayout->addWidget(resultLabel, 1, 0);
    mainLayout->addWidget(m_resultsList, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));

    updateInterface(NavigationMode);

    QVector<Product> products = Repository().loadProducts("../amazon_products.csv");
    m_productTrie.insertProducts(products);
}

void ProductBook::addProduct()
{

}

void ProductBook::findProduct()
{
    QString searchString = m_searchLine->text();
    qDebug() << searchString;
    QVector<Product*> products = m_productTrie.autoComplete(searchString);
    for (Product *product : products) {
        qDebug() << product->getAsin();
        m_resultsList->addItem(product->getAsin());
    }
}

void ProductBook::updateInterface(Mode mode)
{

}
