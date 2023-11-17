#ifndef PRODUCTTRIE_H
#define PRODUCTTRIE_H

#include "product.h"
#include <unordered_map>

class ProductTrie
{
public:
    struct Node {
        QHash<QChar, Node*> children;
        QVector<Product*> products;
    };

    ProductTrie();

    void insertProduct(Product *product);
    void insertProducts(QVector<Product*> products);
    int getCount();
    QVector<Product*> autoComplete(QString searchString);

private:
    Node* m_head;
    unsigned int m_count;

    void insert(QString insertString, Product *product);
    QSet<QString> getAllSubstrings(QString string);
};

#endif // PRODUCTTRIE_H
