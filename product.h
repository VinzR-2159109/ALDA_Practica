//Vinz Roosen & Lars Gielen
#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDate>

class Product
{
public:
    Product();
    Product(const QString &asin, const QString &titel, const QString &imageUrl, const QString &productUrl, float stars, int numberOfReviews, float price, float listPrice, int category, bool isBestSeller, int amountBoughtLastMonth);

    QString getAsin() const;
    QString getTitle() const;
    QString getImageUrl() const;
    QString getProductUrl() const;
    float getStars() const;
    int getNumberOfReviews() const;
    float getPrice() const;
    float getListPrice() const;
    float getDiscount() const;
    int getCategory() const;
    bool getIsBestSeller() const;
    int getAmountBoughtLastMonth() const;

    bool operator<(const Product &other) const;

private:
    QString m_asin;
    QString m_title;
    QString m_imageUrl;
    QString m_productUrl;
    float m_stars;
    int m_numberOfReviews;
    float m_price;
    float m_listPrice;
    float discount;
    int m_category;
    bool m_isBestSeller;
    int m_amountBoughtLastMonth;
};

#endif // PRODUCT_H
