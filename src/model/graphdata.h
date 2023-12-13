#ifndef GRAPHDATA_H
#define GRAPHDATA_H

#include "vertex.h"

#include <QHash>
#include <QVector>

class GraphData
{
public:
    GraphData();
    ~GraphData();

    QVector<Vertex*> getVertices() const;
    QVector<Vertex*> getInfectedVertices() const;
    QMultiHash<Vertex*, Vertex*> getConnections() const;
    QVector<QVector<Vertex*>> getSolutions() const;
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

    void deleteVertex(Vertex* vertex);
    void deleteInfectedVertex(Vertex* vertex);
    void deleteConnection(Vertex* vertex1, Vertex* vertex2);

    void deleteVertexFromString(QString string);
    void deleteInfectedVertexFromString(QString string);
    void deleteConnectionFromString(QString string);
    void deleteSolutionFromString(QString string);

    void deleteAllConnectionFromVertex(Vertex *vertex);

private:
    QHash<QString, Vertex*> m_vertices;
    QHash<QString, Vertex*> m_infectedVertices;
    QMultiHash<Vertex*, Vertex*> m_connections;
    QVector<QVector<Vertex*>> m_solutions;
    int m_days = 0;
};

#endif // GRAPHDATA_H
