#ifndef PRODUCTTRIE_H
#define PRODUCTTRIE_H

#include "product.h"
#include <unordered_map>

class ProductTrie
{
public:

    struct Node {
        std::unordered_map<QChar, Node*> children;
        std::vector<Product*> products;
    };

    ProductTrie();

    void insert(Product *product);
    void autoComplete(QString string);

private:
    Node* m_head;

    void insert(QString insertString, Product *product);
};

#endif // PRODUCTTRIE_H
