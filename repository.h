#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "product.h"

class Repository
{
public:
    QVector<Product> loadProducts(std::string fileName);
};

#endif // REPOSITORY_H
