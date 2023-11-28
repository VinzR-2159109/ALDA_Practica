//Vinz Roosen & Lars Gielen

#ifndef SEARCHBARLAYOUT_H
#define SEARCHBARLAYOUT_H

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>

class SearchBarLayout : public QHBoxLayout
{
    Q_OBJECT

public:
    SearchBarLayout();

    enum class SearchType { Mixed, Asin, Title };

    SearchType getSearchType();
    QString getSearchString();
    void setSearchType(SearchType searchType);

signals:
    /**
     * @brief Gets called when the searchLine changes value
     * @param searchString - the string in the searchLine
     */
    void searchLineChanged(QString searchString);

    /**
     * @brief Gets called when the search type changes value
     * @param searchType - the new search type
     */
    void searchTypeChanged(SearchType searchType);

    /**
     * @brief Gets calles when the searchLine changes value or when the search type changes value
     * @param searchString - the string in the searchLine
     * @param searchType - the new search type
     */
    void searchParamsChanged(QString searchString, SearchType searchType);

private:
    SearchType m_currentSearchType;

    QLineEdit *m_searchLine;
    QPushButton *m_setSearchMixedButton;
    QPushButton *m_setSearchAsinButton;
    QPushButton *m_setSearchTitleButton;

private slots:
    void onMixedButtonClicked();
    void onAsinButtonClicked();
    void onTitleButtonClicked();

    void onSearchLineChanged();
};

#endif // SEARCHBARLAYOUT_H
