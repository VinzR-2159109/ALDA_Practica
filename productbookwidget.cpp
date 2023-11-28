//Vinz Roosen & Lars Gielen
#include "productbookwidget.h"

#include "infoview.h"
#include "productlistitem.h"
#include "productview.h"
#include "repository.h"
#include "searchbarlayout.h"

#include <QLabel>
#include <QSplitter>

ProductBookWidget::ProductBookWidget(QWidget *parent)
    : QWidget(parent),
    m_searchbarLayout(new SearchBarLayout()),
    m_resultsList(new QListWidget()),
    m_productView(new ProductView()),
    m_infoView(new InfoView()),
    m_repository(Repository()),
    m_pageLabel(new QLabel("Pagenumber: 0  (0 results)")),
    m_pageNumber{0},
    m_numberOfResults{0},
    m_btnNextPage(new QPushButton("next page>")),
    m_btnPrevPage(new QPushButton("<previous page"))
{
    // Define Layout ---------------------
    QWidget *leftWidget = new QWidget();
    QWidget *rightWidget = new QWidget();

    QHBoxLayout *pageBtnLayout = new QHBoxLayout();
    pageBtnLayout->addWidget(m_pageLabel);
    pageBtnLayout->addWidget(m_btnPrevPage);
    pageBtnLayout->addWidget(m_btnNextPage);

    QVBoxLayout *leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addLayout(m_searchbarLayout);
    leftLayout->addWidget(m_resultsList);
    leftLayout->addLayout(pageBtnLayout);

    QVBoxLayout *right = new QVBoxLayout(rightWidget);
    right->addWidget(m_productView);
    right->addWidget(m_infoView);

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

    connect(m_searchbarLayout, &SearchBarLayout::searchParamsChanged, this, &ProductBookWidget::onSearchParamsChanged);
    connect(m_resultsList, &QListWidget::itemClicked, this, &ProductBookWidget::displaySelectedProduct);
    connect(m_btnNextPage, &QPushButton::clicked, this, &ProductBookWidget::nextPage);
    connect(m_btnPrevPage, &QPushButton::clicked, this, &ProductBookWidget::prevPage);

    m_infoView->startedLoading();

    loadData();
}

void ProductBookWidget::findProduct(QString searchString, SearchBarLayout::SearchType searchType, bool showSorted)
{
    searchString = searchString.toLower();
    m_resultsList->clear();

    bool isEnd = true;
    int counter = 0;
    int pageCounterBegin = 0;

    auto it = m_pageIndex.find(m_pageNumber);
    if (it != m_pageIndex.end()){
        pageCounterBegin = it.value();
    }

    m_btnPrevPage->setEnabled(false);
    m_btnNextPage->setEnabled(false);

    QVector<Product*> products;

    if (showSorted){
        products = m_productTrie.searchSorted(searchString, 20);
    }
    else {
        products = m_productTrie.search(searchString);
    }

    for (int i = pageCounterBegin; i < products.length(); i++) {
        if (counter >= 20) {
            isEnd = false;
            break;
        }

        if (products.at(i)->getAsin().toLower().contains(searchString) && searchType != SearchBarLayout::SearchType::Title) {
            m_resultsList->addItem(new ProductListItem(products.at(i)->getAsin(), products.at(i)));
            counter++;
        }

        if (products.at(i)->getTitle().toLower().contains(searchString) && searchType != SearchBarLayout::SearchType::Asin){
            m_resultsList->addItem(new ProductListItem(products.at(i)->getTitle(), products.at(i)));
            counter++;
        }
    }

    m_numberOfResults = products.size();

    if (!isEnd) {
        m_btnNextPage->setEnabled(true);
    }

    if (m_pageNumber > 0) {
        m_btnPrevPage->setEnabled(true);
    }

    m_pageIndex.insert(m_pageNumber + 1, pageCounterBegin + counter);

    m_pageLabel->setText(QString("Pagenumber: %1  (%2 results)").arg(m_pageNumber).arg(m_numberOfResults));
}

void ProductBookWidget::onSearchParamsChanged(QString searchString, SearchBarLayout::SearchType searchType)
{
    m_pageIndex.clear();
    m_pageIndex.insert(0, 0);
    m_pageNumber = 0;

    m_pageLabel->setText(QString("Pagenumber: %1  (%2 results)").arg(m_pageNumber).arg(m_numberOfResults));

    findProduct(searchString, searchType, true);
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

void ProductBookWidget::nextPage(){
    m_pageNumber++;
    findProduct(m_searchbarLayout->getSearchString(), m_searchbarLayout->getSearchType(), false);
}

void ProductBookWidget::prevPage(){
    m_pageNumber--;
    findProduct(m_searchbarLayout->getSearchString(), m_searchbarLayout->getSearchType(), false);
}
