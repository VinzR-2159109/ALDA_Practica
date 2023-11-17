#include "repository.h"

#include <QFile>
#include <thread>

Repository::Repository(QObject *parent)
{}

void Repository::loadProducts(const QString &fileName, ProductTrie &trie)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    file.readLine();

    if (!file.isOpen()) {
        file.close();
        return;
    }

    while (!file.atEnd()) {
        QString line = file.readLine();
        handleLine(line, trie);
    }

    file.close();
}

void Repository::handleLine(const QString &line, ProductTrie &trie)
{
    bool flag = false;
    int counter = 0;
    QStringList list(11);

    for (int i = 0; i < line.length(); ++i) {
        if (line[i] == ',' && flag == false) {
            counter++;
            continue;
        }
        else if (line[i] == '\"') {
            flag = !flag;
            continue;
        }
        else if (line[i] == '\n') {
            continue;
        }

        list[counter].append(line[i]);
    }

    Product *newProduct = new Product(
        list[0],
        list[1],
        list[2],
        list[3],
        list[4].toFloat(),
        list[5].toInt(),
        list[6].toFloat(),
        list[7].toFloat(),
        list[8].toInt(),
        list[9][0] == 'T',
        list[10].toInt()
    );

    trie.insertProduct(newProduct);
}
