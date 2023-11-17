#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "product.h"
#include "producttrie.h"

class Repository : public QObject
{
    Q_OBJECT

public:
    Repository(QObject *parent = nullptr);

    void loadProductsThreaded(const QString &fileName, ProductTrie &trie);

signals:
    void setProductLoadedInView();
    void setFinishedLoadingInView();
    void setMessageInView(QString text);

private:
    QString m_fileName;
    int m_loadedAmount;

    void loadProductsInternal(const QString &fileName, ProductTrie &trie);
    void handleLine(QString &line, ProductTrie &trie);
};

#endif // REPOSITORY_H
