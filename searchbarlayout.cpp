#include "searchbarlayout.h"

#include <QLabel>

SearchBarLayout::SearchBarLayout()
{
    m_searchLine = new QLineEdit;
    m_setSearchMixedButton = new QPushButton("Mixed");
    m_setSearchAsinButton = new QPushButton("Asin");
    m_setSearchTitleButton = new QPushButton("Title");

    m_searchLine->setPlaceholderText("Search");

    m_setSearchMixedButton->setFixedWidth(40);
    m_setSearchAsinButton->setFixedWidth(40);
    m_setSearchTitleButton->setFixedWidth(40);

    addWidget(m_searchLine);
    addWidget(m_setSearchAsinButton);
    addWidget(m_setSearchTitleButton);
    addWidget(m_setSearchMixedButton);

    connect(m_setSearchMixedButton, &QPushButton::clicked, this, &SearchBarLayout::onMixedButtonClicked);
    connect(m_setSearchAsinButton, &QPushButton::clicked, this, &SearchBarLayout::onAsinButtonClicked);
    connect(m_setSearchTitleButton, &QPushButton::clicked, this, &SearchBarLayout::onTitleButtonClicked);

    connect(m_searchLine, &QLineEdit::textChanged, this, &SearchBarLayout::onSearchLineChanged);

    setSearchType(SearchType::Mixed);
}

SearchBarLayout::SearchType SearchBarLayout::getSearchType()
{
    return m_currentSearchType;
}

void SearchBarLayout::setSearchType(SearchType searchType)
{
    m_currentSearchType = searchType;
    emit searchTypeChanged(searchType);
    emit searchParamsChanged(m_searchLine->text(), m_currentSearchType);

    switch (searchType) {
    case SearchType::Asin:
        m_setSearchAsinButton->setDisabled(true);
        m_setSearchTitleButton->setDisabled(false);
        m_setSearchMixedButton->setDisabled(false);
        break;
    case SearchType::Title:
        m_setSearchAsinButton->setDisabled(false);
        m_setSearchTitleButton->setDisabled(true);
        m_setSearchMixedButton->setDisabled(false);
        break;
    case SearchType::Mixed:
        m_setSearchAsinButton->setDisabled(false);
        m_setSearchTitleButton->setDisabled(false);
        m_setSearchMixedButton->setDisabled(true);
        break;
    default:
        break;
    }
}

void SearchBarLayout::onMixedButtonClicked()
{
    setSearchType(SearchType::Mixed);
}

void SearchBarLayout::onAsinButtonClicked()
{
    setSearchType(SearchType::Asin);
}

void SearchBarLayout::onTitleButtonClicked()
{
    setSearchType(SearchType::Title);
}

QString SearchBarLayout::getSearchString(){
    return m_searchLine->text();
}

void SearchBarLayout::onSearchLineChanged()
{
    emit searchLineChanged(getSearchString());
    emit searchParamsChanged(getSearchString(), m_currentSearchType);
}


