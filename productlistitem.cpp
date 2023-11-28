//Vinz Roosen & Lars Gielen

#include "productlistitem.h"

ProductListItem::ProductListItem(QString name, Product *product) : QListWidgetItem(name), m_product{product}
{ }

Product *ProductListItem::getProduct() const
{
    return m_product;
}
