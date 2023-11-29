//Vinz Roosen & Lars Gielen

#include "repository.h"

#include <QFile>
#include <thread>

Repository::Repository(QObject *parent) : m_loadedAmount{0}
{}

void Repository::loadProductsThreaded(const QString &fileName, ProductTrie &trie)
{
    m_fileName = fileName;

    std::thread([&] {
        loadProductsInternal(m_fileName, trie);
    }).detach();
}

void Repository::loadProductsInternal(const QString &fileName, ProductTrie &trie)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    if (file.isOpen()) {
        file.readLine();

        while (!file.atEnd()) {

            if (m_loadedAmount >= LIMIT)
                break;

            QString line = file.readLine();
            handleLine(line, trie);

            m_loadedAmount++;
        }

        file.close();
        emit finishedLoading();
    }
    else {
        file.close();
        emit finishedLoading();
        emit error(QString("File %1 can not be opened").arg(fileName));
    }
}

void Repository::handleLine(QString &line, ProductTrie &trie)
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
