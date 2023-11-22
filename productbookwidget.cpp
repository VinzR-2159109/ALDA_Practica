#include "productbookwidget.h"

#include "infoview.h"
#include "productlistitem.h"
#include "productview.h"
#include "repository.h"
#include "searchbarlayout.h"

#include <QSplitter>

ProductBookWidget::ProductBookWidget(QWidget *parent)
    : QWidget(parent)
    , m_repository(Repository())
{
    // create all views
    m_searchbarLayout = new SearchBarLayout();
    m_resultsList = new QListWidget();
    m_productView = new ProductView();
    m_infoView = new InfoView();

    // Define Layout ---------------------
    QWidget *leftWidget = new QWidget();
    QWidget *rightWidget = new QWidget();

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addLayout(m_searchbarLayout);
    leftLayout->addWidget(m_resultsList);

    QVBoxLayout *right = new QVBoxLayout(rightWidget);
    right->addWidget(m_productView);
    right->addLayout(m_infoView);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(leftWidget);
    splitter->addWidget(rightWidget);

    QFrame *splitterLine = new QFrame();
    splitterLine->setFrameShape(QFrame::VLine);
    splitterLine->setFrameShadow(QFrame::Sunken);

    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addWidget(splitter);
    // -----------------------------------

    setWindowTitle("Amazon Products");
    setLayout(mainLayout);

    connect(&m_repository, &Repository::finishedLoading, m_infoView, &InfoView::stoppedLoading);
    connect(&m_repository, &Repository::error, m_infoView, &InfoView::setError);
    connect(&m_productTrie, &ProductTrie::productInserted, m_infoView, &InfoView::setInsertedProduct);
    connect(&m_productTrie, &ProductTrie::searchComplete, m_infoView, &InfoView::setLastSearchTime);

    connect(m_searchbarLayout, &SearchBarLayout::searchParamsChanged, this, &ProductBookWidget::findProduct);
    connect(m_resultsList, &QListWidget::itemClicked, this, &ProductBookWidget::displaySelectedProduct);

    m_infoView->startedLoading();
    loadData();
}

void ProductBookWidget::findProduct(QString searchString, SearchBarLayout::SearchType searchType)
{
    searchString = searchString.toLower();
    QSet<Product*> products = m_productTrie.search(searchString);

    m_resultsList->clear();

    int counter = 0;
    for (Product *product : products) {
        if (counter >= 20) break;

        if (product->getAsin().toLower().contains(searchString) && searchType != SearchBarLayout::SearchType::Title) {
            m_resultsList->addItem(new ProductListItem(product->getAsin(), product));
        }

        if (product->getTitle().toLower().contains(searchString) && searchType != SearchBarLayout::SearchType::Asin){
            m_resultsList->addItem(new ProductListItem(product->getTitle(), product));
        }

        counter++;
    }
}

void ProductBookWidget::loadData()
{
    m_repository.loadProductsThreaded("../amazon_products.csv", m_productTrie);
}

void ProductBookWidget::displaySelectedProduct(QListWidgetItem *item)
{
    Product *product = static_cast<ProductListItem*>(item)->getProduct();
    m_productView->setProduct(product);
}
