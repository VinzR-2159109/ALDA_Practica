#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include "vertex.h"
#include <QVector>

class GraphData
{
public:
    GraphData();

    QVector<Vertex *> getVertices() const;
    QVector<Vertex *> getInfectedVertices() const;
    QVector<std::pair<Vertex *, Vertex *> > getConnections() const;
    QVector<QVector<Vertex *> > getSolutions() const;
    int getDays() const;

    /**
     * @brief adds a vertex to the graph
     * @param newVertex
     */
    void addVertex(Vertex *newVertex);

    /**
     * @brief adds and sets a, infected vertex
     * @param string
     */
    void addInfectedVertexFromString(QString &string);

    /**
     * @brief adds a connection, string is of format "A, B"
     * @param string
     */
    void addConnectionFromString(QString &string);

    /**
     * @brief adds a solution, string is of format "A, B, C, ..."
     * @param string
     */
    void addSolutionFromString(QString &string);

    /**
     * @brief setDays
     * @param newDays
     */
    void setDays(int newDays);

private:
    QVector<Vertex*> m_vertices;
    QVector<Vertex*> m_infectedVertices;
    QVector<std::pair<Vertex*, Vertex*>> m_connections;
    QVector<QVector<Vertex*>> m_solutions;
    int m_days = 0;
};

#endif // GRAPHDATA_H
