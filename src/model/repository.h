#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "graphdata.h"
#include "vertex.h"

#include <QString>
#include <QVector>
#include <tuple>

class Repository
{
public:

    struct Data
    {
        GraphData *graphData;
        bool loadSucces = false;
    };

    Repository();

    Data LoadFile(const QString &filePath);
    void saveFile(const QString &filePath, const GraphData *data);

private:

};

#endif // REPOSITORY_H
