//Vinz Roosen & Lars Gielen
#ifndef PRODUCTLISTITEM_H
#define PRODUCTLISTITEM_H

#include "product.h"

#include <QListWidgetItem>

class ProductListItem : public QListWidgetItem
{
public:
    ProductListItem(QString name, Product *product);

    /**
     * @brief Get the product from this item
     * @return
     */
    Product *getProduct() const;

private:
    Product *m_product;
};

#endif // PRODUCTLISTITEM_H
