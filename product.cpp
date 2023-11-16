#include "product.h"

Product::Product(const QString &asin, const QString &titel, const QString &imageUrl, const QString &productUrl, float stars, int numberOfReviews, float price, float listPrice, int category, bool isBestSeller) : m_asin(asin),
    m_titel(titel),
    m_imageUrl(imageUrl),
    m_productUrl(productUrl),
    m_stars(stars),
    m_numberOfReviews(numberOfReviews),
    m_price(price),
    m_listPrice(listPrice),
    m_category(category),
    isBestSeller(isBestSeller)
{}

QString Product::getAsin() const
{
    return m_asin;
}

QString Product::getTitel() const
{
    return m_titel;
}

QString Product::getImageUrl() const
{
    return m_imageUrl;
}

QString Product::getProductUrl() const
{
    return m_productUrl;
}

float Product::getStars() const
{
    return m_stars;
}

int Product::getNumberOfReviews() const
{
    return m_numberOfReviews;
}

float Product::getPrice() const
{
    return m_price;
}

float Product::getListPrice() const
{
    return m_listPrice;
}

int Product::getCategory() const
{
    return m_category;
}

bool Product::getIsBestSeller() const
{
    return isBestSeller;
}
