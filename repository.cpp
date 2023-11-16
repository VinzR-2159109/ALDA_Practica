#include "repository.h"

#include <QFile>

QVector<Product> Repository::loadProducts(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    file.readLine();

    if (!file.isOpen()) {
        file.close();
        qDebug() << "File not found";
        return QVector<Product>();
    }

    QVector<Product> products;

    while (!file.atEnd()) {

        QString line = file.readLine();
        QStringList list(11);

        bool flag = false;
        int counter = 0;
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

        products.emplace_back(
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

        counter++;
    }

    file.close();

    return products;
}
