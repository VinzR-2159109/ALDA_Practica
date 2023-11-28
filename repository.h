//Vinz Roosen & Lars Gielen
#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "product.h"
#include "producttrie.h"

class Repository : public QObject
{
    Q_OBJECT

public:
    Repository(QObject *parent = nullptr);

    /**
     * @brief Loads the file from fileName the background on multiple threads
     * @param fileName - the file to load
     * @param trie - the ProductTrie in which to insert the Products
     */
    void loadProductsThreaded(const QString &fileName, ProductTrie &trie);

signals:
    /**
     * @brief Gets called when the file has stopped loading
     */
    void finishedLoading();

    /**
     * @brief Gets called when the file can't open
     * @param errorText - the text of the error
     */
    void error(QString errorText);

private:
    const static int LIMIT = 5000;
    QString m_fileName;
    int m_loadedAmount;

    void loadProductsInternal(const QString &fileName, ProductTrie &trie);
    void handleLine(QString &line, ProductTrie &trie);
};

#endif // REPOSITORY_H
