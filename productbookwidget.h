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
    QHash<int, int> m_pageIndex;

    QPushButton *m_btnNextPage;
    QPushButton *m_btnPrevPage;

    /**
     * @brief Loads the data from the file
     */
    void loadData();

    /**
     * @brief displays the selected item from m_resultsList
     * @param item - the item to display
     */
    void displaySelectedProduct(QListWidgetItem *item);
    void nextPage();
    void prevPage();
private slots:

    /**
     * @brief find all products that have searchstring as a substring, filter with searchType
     * @param searchString - find all products that have searchstring as a substring
     * @param searchType - only display these products in m_resultsList
     */
    void findProduct(QString searchString, SearchBarLayout::SearchType searchType);

    void onSearchParamsChanged(QString searchString, SearchBarLayout::SearchType searchType);
};

#endif // PRODUCTBOOKWIDGET_H
