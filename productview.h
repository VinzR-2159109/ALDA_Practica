#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include "product.h"

#include <QLabel>
#include <QNetworkReply>
#include <QTableWidget>

class ProductView : public QWidget
{
public:
    ProductView();

    /**
     * @brief Set a product in this view
     * @param product - the product to set
     */
    void setProduct(Product *product);
private:
    QTableWidget *m_table;
    QLabel *m_imageLabel;
    QNetworkAccessManager *m_networkManager;

private slots:
    void onImageDownloaded(QNetworkReply *reply);
};

#endif // PRODUCTVIEW_H
