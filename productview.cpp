#include "productview.h"

ProductView::ProductView()
{
    QStringList headers;
    headers << "ASIN" << "Title" << "Stars" << "Price" << "List price" << "Discount";

    setColumnCount(6);
    setHorizontalHeaderLabels(headers);
}

void ProductView::setProduct(Product *product)
{
    removeRow(0);
    insertRow(0);

    setItem(0, 0, new QTableWidgetItem(product->getAsin()));
    setItem(0, 1, new QTableWidgetItem(product->getTitle()));
    setItem(0, 2, new QTableWidgetItem(QString::number(product->getStars())));
    setItem(0, 3, new QTableWidgetItem(QString::number(product->getPrice())));
    setItem(0, 4, new QTableWidgetItem(QString::number(product->getListPrice())));
    setItem(0, 5, new QTableWidgetItem(QString::number(product->getDiscount()) + " %"));
}
