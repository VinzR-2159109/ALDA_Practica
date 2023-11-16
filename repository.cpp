#include "repository.h"
#include <iostream>
#include <fstream>

QVector<Product> Repository::loadProducts(std::string fileName)
{
    std::ifstream file;
    std::string constactString;

    file.open(fileName);
    if (!file.is_open()) {
        file.close();
        std::cout << "-- Failed to open file " << fileName << " --\n";
    }

    QVector<Product> products;

    while (true) {
        if (file.eof())
            break;

        std::string asin, title, imgUrl, productURL, stars, reviews, price, listPrice, category_id, isBestSeller, boughtInLastMonth ;

        std::getline(file, asin, ',');
        std::getline(file, title, ',');
        std::getline(file, imgUrl, ',');
        std::getline(file, stars, ',');
        std::getline(file, reviews, ',');
        std::getline(file, price, ',');
        std::getline(file, listPrice, ',');
        std::getline(file, category_id, ',');
        std::getline(file, isBestSeller, ',');
        std::getline(file, boughtInLastMonth, '\n');

        products.emplace_back(asin, title, imgUrl, productURL, stars, reviews, price, listPrice, category_id, isBestSeller, boughtInLastMonth);
    }

    file.close();

    return products;
}
