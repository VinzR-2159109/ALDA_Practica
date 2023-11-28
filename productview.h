//Vinz Roosen & Lars Gielen
#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include "product.h"
#include <QLabel>
#include <QNetworkReply>
#include <QTableWidget>

class ProductView : public QTableWidget
{
public:
    ProductView();

    /**
     * @brief Set a product in this view
     * @param product - the product to set
     */
    void setProduct(Product *product);
private:
    QNetworkAccessManager *m_networkManager;

    QLabel *m_titleLabel;
    QLabel *m_subTitleLabel;
    QLabel *m_ratingLabel;
    QLabel *m_priceLabel;
    QLabel *m_discountLabel;
    QLabel *m_imageLabel;

private slots:
    void onImageDownloaded(QNetworkReply *reply);
};

#endif // PRODUCTVIEW_H
