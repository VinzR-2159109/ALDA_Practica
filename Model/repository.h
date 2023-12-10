#ifndef REPOSITORY_H
#define REPOSITORY_H

#include "vertex.h"

#include <QString>
#include <QVector>
#include <tuple>

class Repository
{
public:

    struct Data
    {
        /**
         * @brief A list of all vertices
         */
        QVector<Vertex*> vertices;

        /**
         * @brief A list of tupples of 2 ints that have a connection from first to second
         */
        QVector<std::pair<Vertex*, Vertex*>> connections;

        /**
         * @brief A list of ints of the ifectedd vertices
         */
        QVector<Vertex*> infectedVertices;

        /**
         * @brief The amount of days
         */
        int days;

        /**
         * @brief A list of all possible solutions
         */
        QVector<QVector<Vertex*>> possibleSolutions;

        bool loadSucces = false;
    };

    Repository();

    Data LoadFile(QString filePath);

private:

};

#endif // REPOSITORY_H
