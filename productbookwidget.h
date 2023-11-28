//Vinz Roosen & Lars Gielen

#ifndef PRODUCTBOOKWIDGET_H
#define PRODUCTBOOKWIDGET_H

#include "producttrie.h"
#include "repository.h"

#include "infoview.h"
#include "productview.h"
#include "searchbarlayout.h"

#include <QListWidget>

class ProductBookWidget : public QWidget
{
    Q_OBJECT

public:
    static const int SEARCHLAYOUTWIDTH = 200;

    ProductBookWidget(QWidget *parent = nullptr);

private:

    SearchBarLayout *m_searchbarLayout;
    QListWidget *m_resultsList;
    ProductView *m_productView;
    InfoView *m_infoView;

    ProductTrie m_productTrie;
    Repository m_repository;

    QLabel *m_pageLabel;
    int m_pageNumber;
    int m_numberOfResults;
    QHash<int, int> m_pageIndex;
    QPushButton *m_btnNextPage;
    QPushButton *m_btnPrevPage;

    void loadData();
    void displaySelectedProduct(QListWidgetItem *item);
    void nextPage();
    void prevPage();

private slots:

    /**
     * @brief find all products that have searchstring as a substring, filter with searchType
     * @param searchString - find all products that have searchstring as a substring
     * @param searchType - only display these products in m_resultsList
     */
    void findProduct(QString searchString, SearchBarLayout::SearchType searchType, bool showInPages);

    void onSearchParamsChanged(QString searchString, SearchBarLayout::SearchType searchType);
};

#endif // PRODUCTBOOKWIDGET_H
