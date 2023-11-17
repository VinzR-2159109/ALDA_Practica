#ifndef PRODUCTTRIE_H
#define PRODUCTTRIE_H

#include "product.h"
#include <unordered_map>

class ProductTrie : public QObject
{
    Q_OBJECT
public:

    struct Node {
        std::unordered_map<QChar, Node*> children;
        QVector<Product*> products;
    };

    ProductTrie();

    void insertProduct(Product *product);
    void insertProducts(QVector<Product*> products);
    QVector<Product*> autoComplete(QString searchString);

signals:
    void setProductInsertInView(QString text);

private:
    Node* m_head;
    unsigned int m_count;

    void insert(QString insertString, Product *product);
    QStringList getAllSubstrings(QString string);
};

#endif // PRODUCTTRIE_H
