#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "product.h"
#include "producttrie.h"

class Repository
{
public:
    Repository(QObject *parent = nullptr);

    static void loadProducts(QString &fileName, ProductTrie &trie);

private:
    void handleLine(const QString &line, ProductTrie &trie);

};

#endif // REPOSITORY_H
