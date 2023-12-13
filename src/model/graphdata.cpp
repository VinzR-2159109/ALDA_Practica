#include "graphdata.h"

GraphData::GraphData()
{}

GraphData::~GraphData()
{
    for (const auto &vertex : getVertices()) {
        deleteVertex(vertex);
    }
}

QVector<Vertex *> GraphData::getVertices() const
{
    return QVector<Vertex*>(m_vertices.begin(), m_vertices.end());;
}

QVector<Vertex *> GraphData::getInfectedVertices() const
{
    return QVector<Vertex*>(m_infectedVertices.begin(), m_infectedVertices.end());;
}

QMultiHash<Vertex *, Vertex *> GraphData::getConnections() const
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
    if (!m_vertices.contains(newVertex->getName())) {
        m_vertices.insert(newVertex->getName(), newVertex);
    }
}

void GraphData::addInfectedVertexFromString(QString &string)
{
    Vertex *vertex = m_vertices.value(string);

    if (!vertex || vertex->getIsInfected()) return;

    vertex->setInfected(true);
    m_infectedVertices.insert(vertex->getName(), vertex);
}

void GraphData::addConnectionFromString(QString &string)
{
    QStringList vertexNames = string.replace(' ', "").split(",");
    if (vertexNames.size() != 2)
        return;

    Vertex *vertex1 = m_vertices.value(vertexNames[0]);
    Vertex *vertex2 = m_vertices.value(vertexNames[1]);

    if (!vertex1 || !vertex2)
        return;

    if (m_connections.values(vertex1).contains(vertex2))
        return;

    m_connections.insert(vertex1, vertex2);
}

void GraphData::addSolutionFromString(QString &string)
{
    QStringList vertexNames = string.replace(' ', "").split(",");
    QVector<Vertex*> solution = QVector<Vertex*>();

    for (const auto &vertexName : vertexNames) {
        Vertex *vertex = m_vertices.value(vertexName);

        if (!vertex)
            return;

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
    if (!vertex)
        return;

    deleteInfectedVertex(vertex);
    deleteAllConnectionFromVertex(vertex);
    m_vertices.remove(vertex->getName());

    delete vertex;
}

void GraphData::deleteInfectedVertex(Vertex *vertex)
{    
    vertex->setInfected(false);
    m_infectedVertices.remove(vertex->getName());
}

void GraphData::deleteConnection(Vertex *vertex1, Vertex *vertex2)
{
    m_connections.remove(vertex1, vertex2);
}

void GraphData::deleteAllConnectionFromVertex(Vertex *vertex)
{
    m_connections.remove(vertex);
}

void GraphData::deleteVertexFromString(QString string)
{
    deleteVertex(m_vertices.value(string));
}

void GraphData::deleteInfectedVertexFromString(QString string)
{
    deleteInfectedVertex(m_infectedVertices.value(string));
}

void GraphData::deleteConnectionFromString(QString string)
{
    QStringList vertexNames = string.replace(' ', "").split("->");
    if (vertexNames.size() != 2)
        return;

    Vertex *vertex1 = m_vertices.value(vertexNames[0]);
    Vertex *vertex2 = m_vertices.value(vertexNames[1]);

    deleteConnection(vertex1, vertex2);
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
