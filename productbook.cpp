#include "productbook.h"
#include "repository.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>

#include <thread>

ProductBook::ProductBook(QWidget *parent)
    : QWidget(parent)
    , m_repository(Repository())
{
    connect(&m_productTrie, &ProductTrie::setProductInsertInView, this, &ProductBook::setStatusMessage);

    // create status label
    m_statusText = new QLabel("");
    m_statusText->show();

    // create search label
    QLabel *searchLabel = new QLabel("Search:");
    m_searchLine = new QLineEdit;

    // create result list
    QLabel *resultLabel = new QLabel("results:");
    m_resultsList = new QListWidget();

    // create buttons
    m_addButton = new QPushButton("Search");
    m_addButton->show();
    m_loadDataButton = new QPushButton("Load");
    m_loadDataButton->show();

    // connect clicked events to correct method
    connect(m_addButton, &QPushButton::clicked, this, &ProductBook::findProduct);
    connect(m_loadDataButton, &QPushButton::clicked, this, &ProductBook::loadData);
    connect(m_searchLine, &QLineEdit::textChanged, this, &ProductBook::findProduct);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(m_addButton, Qt::AlignTop);
    buttonLayout1->addWidget(m_loadDataButton, Qt::AlignTop);
    buttonLayout1->addStretch();

    // create main layout
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(searchLabel, 0, 0);
    mainLayout->addWidget(m_searchLine, 0, 1);
    mainLayout->addWidget(resultLabel, 1, 0);
    mainLayout->addWidget(m_resultsList, 1, 1);
    mainLayout->addLayout(buttonLayout1, 1, 2);
    mainLayout->addWidget(m_statusText, 2, 1);

    setLayout(mainLayout);
    setWindowTitle(tr("Simple Address Book"));
}

void ProductBook::addProduct()
{

}

void ProductBook::findProduct()
{
    m_resultsList->clear();

    QString searchString = m_searchLine->text();
    QVector<Product*> products = m_productTrie.autoComplete(searchString);

    int counter = 0;
    for (Product *product : products) {
        if (counter >= 20) break;
        counter++;
        m_resultsList->addItem(product->getAsin());
    }
}

void ProductBook::loadData()
{
    Repository().loadProducts("../amazon_products.csv", m_productTrie);
}

void ProductBook::updateInterface(Mode mode)
{

}

void ProductBook::setStatusMessage(const QString &text)
{
    m_statusText->setText(text);
}
