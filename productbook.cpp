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
    connect(&m_repository, &Repository::setMessageInView, this, &ProductBook::setStatusMessage);
    connect(&m_repository, &Repository::setProductLoadedInView, this, &ProductBook::onLoadProduct);
    connect(&m_repository, &Repository::setFinishedLoadingInView, this, &ProductBook::onFinischLoading);

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
    m_searchButton = new QPushButton("Search");
    m_searchButton->show();
    m_loadDataButton = new QPushButton("Load");
    m_loadDataButton->show();

    // connect clicked events to correct method
    connect(m_searchButton, &QPushButton::clicked, this, &ProductBook::findProduct);
    connect(m_loadDataButton, &QPushButton::clicked, this, &ProductBook::loadData);
    connect(m_searchLine, &QLineEdit::textChanged, this, &ProductBook::findProduct);

    // create edit buttons layout
    QVBoxLayout *buttonLayout1 = new QVBoxLayout;
    buttonLayout1->addWidget(m_searchButton, Qt::AlignTop);
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

    updateInterface(Mode::UsingMode);
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

void ProductBook::onLoadProduct()
{
    setStatusMessage(QString("Loaded %1 products").arg(m_productTrie.getCount()));
}

void ProductBook::onFinischLoading()
{
    setStatusMessage(QString("Finished loading"));
    updateInterface(Mode::UsingMode);
}

void ProductBook::loadData()
{
    updateInterface(Mode::LoadingMode);
    m_repository.loadProductsThreaded("../amazon_products.csv", m_productTrie);
}

void ProductBook::updateInterface(Mode mode)
{
    switch (mode) {
    case Mode::LoadingMode:
        m_searchButton->setEnabled(false);
        m_loadDataButton->setEnabled(false);
        m_searchLine->setEnabled(false);
        break;
    case Mode::UsingMode:
        m_searchButton->setEnabled(true);
        m_loadDataButton->setEnabled(true);
        m_searchLine->setEnabled(true);
        break;
    default:
        break;
    }
}

void ProductBook::setStatusMessage(const QString &text)
{
    m_statusText->setText(text);
}
