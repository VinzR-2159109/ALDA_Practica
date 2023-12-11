#include "graphdata.h"

GraphData::GraphData()
{}

QVector<Vertex *> GraphData::getVertices() const
{
    return m_vertices;
}

QVector<Vertex *> GraphData::getInfectedVertices() const
{
    return m_infectedVertices;
}

QVector<std::pair<Vertex *, Vertex *> > GraphData::getConnections() const
{
    return m_connections;
}

QVector<QVector<Vertex *> > GraphData::getSolutions() const
{
    return m_solutions;
}

int GraphData::getDays() const
{
    return m_days;
}

void GraphData::addVertex(Vertex *newVertex)
{
    m_vertices.push_back(newVertex);
}

void GraphData::addInfectedVertexFromString(QString &string)
{
    Vertex *vertex;
    for (const auto v : m_vertices) {
        if (v->getName() == string)
            vertex = v;
    }
    vertex->setInfected(true);
    m_infectedVertices.push_back(vertex);
}

void GraphData::addConnectionFromString(QString &string)
{
    QStringList vertexNames = string.replace(' ', "").split(",");
    Vertex *vertex1, *vertex2;
    for (const auto vertex : m_vertices) {
        if (vertex->getName() == vertexNames[0])
            vertex1 = vertex;

        if (vertex->getName() == vertexNames[1])
            vertex2 = vertex;
    }
    m_connections.push_back(std::make_pair(vertex1, vertex2));
}

void GraphData::addSolutionFromString(QString &string)
{
    QStringList vertexNames = string.replace(' ', "").split(",");
    QVector<Vertex*> solution = QVector<Vertex*>();
    for (const auto &vertexName : vertexNames) {
        Vertex *vertex;
        for (const auto v : m_vertices) {
            if (v->getName() == vertexName)
                vertex = v;
        }

        solution.push_back(vertex);
    }

    m_solutions.push_back(solution);
}

void GraphData::setDays(int newDays)
{
    m_days = newDays;
}
