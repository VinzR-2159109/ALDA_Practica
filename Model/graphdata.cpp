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
    Vertex *vertex = nullptr;
    for (const auto v : m_vertices) {
        if (v->getName() == newVertex->getName())
            vertex = v;
    }

    if (!vertex) {
        m_vertices.push_back(newVertex);
    }
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

void GraphData::deleteVertex(Vertex *vertex)
{
    deleteInfectedVertex(vertex);
    deleteAllConnectionFromVertex(vertex);
    m_vertices.removeAt(m_vertices.indexOf(vertex));
}

void GraphData::deleteInfectedVertex(Vertex *vertex)
{
    vertex->setInfected(false);

    int index = m_infectedVertices.indexOf(vertex);

    if (index >= 0) {
        m_infectedVertices.removeAt(index);
    }
}

void GraphData::deleteVertexFromString(QString string)
{
    Vertex *vertex = nullptr;

    for (int i = 0; i < m_vertices.size(); i++) {
        if (m_vertices[i]->getName() == string) {
            vertex = m_vertices[i];
            break;
        }
    }

    if (vertex) deleteVertex(vertex);
}

void GraphData::deleteInfectedVertexFromString(QString string)
{
    Vertex *vertex = nullptr;

    for (int i = 0; i < m_infectedVertices.size(); i++) {
        if (m_infectedVertices[i]->getName() == string) {
            vertex = m_infectedVertices[i];
            break;
        }
    }

    if (vertex) deleteInfectedVertex(vertex);
}

void GraphData::deleteConnectionFromString(QString string)
{
    QStringList vertexNames = string.replace(' ', "").split("->");
    for (int i = 0; i < m_connections.size(); i++) {
        if (m_connections[i].first->getName() == vertexNames[0] && m_connections[i].second->getName() == vertexNames[1]) {
            m_connections.removeAt(i);
            break;
        }
    }
}

void GraphData::deleteSolutionFromString(QString string)
{
    QStringList vertexNames = string.replace(' ', "").split(",");
    for (int i = m_solutions.size() - 1; i >= 0; i--) {
        if (m_solutions[i].size() != vertexNames.size())
            continue;

        for (int j = 0; j < vertexNames.size(); j++) {
            if (m_solutions[i][j]->getName() == vertexNames[j]) {
                m_solutions.removeAt(i);
                break;
            }
        }
    }
}

void GraphData::deleteAllConnectionFromVertex(Vertex *vertex)
{
    for (int i = m_connections.size() - 1; i >= 0; i--) {
        if (m_connections[i].first == vertex || m_connections[i].second == vertex) {
            m_connections.removeAt(i);
        }
    }
}
