#include "productbook.h"
#include "repository.h"

#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QScrollArea>

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
    m_loadDataButton = new QPushButton("Load");
    m_loadDataButton->show();

    // connect clicked events to correct method
    connect(m_loadDataButton, &QPushButton::clicked, this, &ProductBook::loadData);
    connect(m_searchLine, &QLineEdit::textChanged, this, &ProductBook::findProduct);
    connect(m_resultsList, &QListWidget::itemClicked, this, &ProductBook::displaySelectedProduct);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(m_loadDataButton, Qt::AlignTop);
    buttonLayout1->addStretch();

    // create grid layout
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(searchLabel, 0, 0);
    gridLayout->addWidget(m_searchLine, 0, 1);
    gridLayout->addWidget(resultLabel, 1, 0);
    gridLayout->addWidget(m_resultsList, 1, 1);
    gridLayout->addLayout(buttonLayout1, 2, 1);
    gridLayout->addWidget(m_statusText, 3, 1);

    m_productTable = new QTableWidget(this);
    m_productTable->setColumnCount(4);

    QStringList headers;
    headers << "ASIN" << "Title" << "Stars" << "Price";
    m_productTable->setHorizontalHeaderLabels(headers);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(m_productTable);

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
    m_products = m_productTrie.autoComplete(searchString);

    int counter = 0;
    for (Product *product : m_products) {
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

void ProductBook::showProductInTable( Product &product)
{
    m_productTable->insertRow(0);

    m_productTable->setItem(0, 0, new QTableWidgetItem(product.getAsin()));
    m_productTable->setItem(0, 1, new QTableWidgetItem(product.getTitle()));
    m_productTable->setItem(0, 2, new QTableWidgetItem(QString::number(product.getStars())));
    //discount
    m_productTable->setItem(0, 3, new QTableWidgetItem(QString::number(product.getPrice())));
}

void ProductBook::displaySelectedProduct(QListWidgetItem *item)
{
    int selectedIndex = m_resultsList->row(item);
    m_productTable->removeRow(0);

    if (selectedIndex >= 0 && selectedIndex < m_products.size()) {
        showProductInTable(*m_products[selectedIndex]);
    }
}

void ProductBook::setStatusMessage(const QString &text)
{
    m_statusText->setText(text);
}

