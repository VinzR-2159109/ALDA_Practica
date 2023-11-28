//Vinz Roosen & Lars Gielen
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
        QSet<Product*> products;
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
    QVector<Product*> search(QString searchString);

    /**
     * @brief Finds and returns an amount (numberOfSortedElements) of products with that have searchString as a substring, sorted on discount
     * @param searchString - the string to search
     * @param numberOfSortedElements - the amount of products to return
     * @return Returns an amount (numberOfSortedElements) product pointers that have searchString as a substring
     */
    QVector<Product*> searchSorted(QString searchString, int numberOfSortedElements);

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
     * @brief Creates and returns all prefixes of the given string
     * @param string - a strings for which to create all prefixes
     * @return Returns a QStringList of all prefixes
     */
    QStringList createAllSuffixes(QString string);

    void addToCSV(int value, const std::string& filename);
};

#endif // PRODUCTTRIE_H
