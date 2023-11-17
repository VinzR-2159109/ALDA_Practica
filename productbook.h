#ifndef PRODUCTBOOK_H
#define PRODUCTBOOK_H

#include "producttrie.h"
#include "repository.h"

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QLabel>

#include <QListWidget>

class ProductBook : public QWidget
{
    Q_OBJECT

public:
    ProductBook(QWidget *parent = nullptr);

public slots:
    void addProduct();
    void findProduct();

private:
    enum Mode { NavigationMode, AddingMode, EditingMode };

    ProductTrie m_productTrie;
    Repository m_repository;

    QPushButton *m_addButton;
    QPushButton *m_loadDataButton;

    QLabel *m_statusText;
    QLineEdit *m_searchLine;
    QListWidget *m_resultsList;

    Mode m_currentMode;

    void loadData();
    void updateInterface(Mode mode);

private slots:
    void setStatusMessage(const QString &text);
};

#endif // PRODUCTBOOK_H
