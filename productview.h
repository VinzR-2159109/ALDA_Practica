#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include "product.h"

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
};

#endif // PRODUCTVIEW_H
