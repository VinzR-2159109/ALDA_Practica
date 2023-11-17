#include "producttrie.h"

ProductTrie::ProductTrie()
    : m_head{new Node}
    , m_count{0}
{ }

void ProductTrie::insertProduct(Product *product)
{
    m_count++;
    QSet<QString> substrings = getAllSubstrings(product->getAsin());
    for (const QString &string : substrings) {
        insert(string, product);
    }

    substrings = getAllSubstrings(product->getTitle());
    for (const QString &string : substrings) {
        insert(string, product);
    }
}

void ProductTrie::insertProducts(QVector<Product*> products)
{
    for (int i = 0; i < products.count(); ++i) {
        insertProduct(products[i]);
    }
}

int ProductTrie::getCount()
{
    return m_count;
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

QSet<QString> ProductTrie::getAllSubstrings(QString string)
{
    QSet<QString> substrings = QSet<QString>();
    for (int i = 0; i < string.length(); ++i) {
        for (int j = 1; j <= string.length() - i; ++j) {
            substrings.insert(string.mid(i, j));
        }
    }

    return substrings;
}
