#ifndef PRODUCTTRIE_H
#define PRODUCTTRIE_H

#include "product.h"
#include <unordered_map>

class ProductTrie : public QObject
{
    Q_OBJECT

public:
    struct Node {
        QHash<QChar, Node*> children;
        QMultiMap<float, Product*> products;
    };

    ProductTrie();

    /**
     * @brief Inserts a new product in the trie
     * @param product - the pointer of the product to insert
     */
    void insertProduct(Product *product);

    /**
     * @brief Finds and returns all the products that have searchString as a substring
     * @param searchString - the string to search
     * @return Returns all product pointers that have searchString as a substring
     */
    QMultiMap<float, Product*> autoComplete(QString searchString);

signals:
    /**
     * @brief Gets calles when a search is completed
     * @param timeTaken - the time it took to find all products
     */
    void searchComplete(long long timeTaken);

    /**
     * @brief Gets called when a new product is inserted
     * @param timeTaken - the time it took to insert the product
     */
    void productInserted(long long timeTaken);

private:
    Node* m_head;

    void insertProductInternal(QString insertString, Product *product);

    /**
     * @brief Creates and returns all unique substrings of all string given to it
     * @param strings - a list of all strings for which to create substrings
     * @return Returns a QSet of all unique substrings
     */
    QSet<QString> createAllUniqueSearchStrings(QStringList strings);
};

#endif // PRODUCTTRIE_H
