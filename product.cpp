#include "product.h"

Product::Product()
    : m_asin(""),
    m_title(""),
    m_imageUrl(""),
    m_productUrl(""),
    m_stars(0),
    m_numberOfReviews(0),
    m_price(0),
    m_listPrice(0),
    m_category(0),
    m_isBestSeller(0),
    m_amountBoughtLastMonth(0)
{ }

Product::Product(const QString &asin, const QString &titel, const QString &imageUrl, const QString &productUrl, float stars, int numberOfReviews, float price, float listPrice, int category, bool isBestSeller, int amountBoughtLastMonth)
    : m_asin(asin),
    m_title(titel),
    m_imageUrl(imageUrl),
    m_productUrl(productUrl),
    m_stars(stars),
    m_numberOfReviews(numberOfReviews),
    m_price(price),
    m_listPrice(listPrice),
    m_category(category),
    m_isBestSeller(isBestSeller),
    m_amountBoughtLastMonth(amountBoughtLastMonth)
{}

QString Product::getAsin() const
{
    return m_asin;
}

QString Product::getTitle() const
{
    return m_title;
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
    return m_isBestSeller;
}

int Product::getAmountBoughtLastMonth() const
{
    return m_amountBoughtLastMonth;
}
