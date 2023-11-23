#ifndef INFOVIEW_H
#define INFOVIEW_H

#include <QLabel>
#include <QTime>
#include <QVBoxLayout>

class InfoView : public QWidget
{
public:
    InfoView();

public slots:
    /**
     * @brief Sets the information about the inserted products
     * @param loadTime - the time it took to insert the product in the trie in ms
     */
    void setInsertedProduct(long long loadTime);

    /**
     * @brief Sets the information about the time it took for the last search operation
     * @param searchTime - the time it took to find all products with a substring in the trie in µs
     */
    void setLastSearchTime(int searchTime);

    /**
     * @brief Sets the information about when the file started to load
     */
    void startedLoading();

    /**
     * @brief Sets the information about when the file stopped to load
     */
    void stoppedLoading();

    /**
     * @brief Sets the time sinds startedLoading was called
     */
    void setLoadingTime();

    /**
     * @brief Sets an error message instead of the other data
     * @param errorMessage - the message of the error
     */
    void setError(QString errorMessage);

private:
    QLabel *m_loadedProducts;
    QLabel *m_lastSearchTime;
    QLabel *m_averageSearchTime;
    QLabel *m_lastLoadTime;
    QLabel *m_averageLoadTime;
    QLabel *m_loadingTime;

    unsigned long long m_searchTimeSum;
    int m_searchAmount;

    unsigned long long m_loadTimeSum;
    int m_loadAmount;

    QTime m_startTime;
};

#endif // INFOVIEW_H
