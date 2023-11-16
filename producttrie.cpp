#include "producttrie.h"

ProductTrie::ProductTrie() : m_head{new Node}
{ }

void ProductTrie::insertProduct(Product product)
{
    Product *newProduct = new Product(product);
    insert(newProduct->getAsin(), newProduct);
}

void ProductTrie::insertProducts(QVector<Product> products)
{
    for (int i = 0; i < products.count(); ++i) {
        insertProduct(products[i]);
    }
}

QVector<Product*> ProductTrie::autoComplete(QString searchString)
{
    Node *currentNode = m_head;

    for (QChar value : searchString) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            return QVector<Product*>();
        }

        currentNode = currentNode->children[value];
    }

    return currentNode->products;
}

void ProductTrie::insert(QString insertString, Product *product)
{
    Node *currentNode = m_head;

    for (QChar value : insertString) {
        if (currentNode->children.find(value) == currentNode->children.end()) {
            currentNode->children[value] = new Node;
        }

        currentNode = currentNode->children[value];
    }

    currentNode->products.push_back(product);
}
