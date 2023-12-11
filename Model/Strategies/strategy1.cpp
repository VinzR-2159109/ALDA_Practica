#include "strategy1.h"

#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

QVector<Vertex*> Strategy1::execute()
{
    createGraph();
    return findSources();
}

void Strategy1::createGraph()
{
    for (const auto &connection : m_data.getConnections()) {
        m_graph.insert(connection.first, connection.second);
    }
}

QVector<Vertex*> Strategy1::findSources()
{
    QVector<Vertex*> sources;

    for (const auto &vertex : m_data.getVertices()) {
        if (checkIfSource(vertex)) {
            sources.push_back(vertex);
        }
    }

    return sources;
}

bool Strategy1::checkIfSource(Vertex* startVertex)
{
    bool isSource = true;

    QQueue<Vertex*> queue;
    QSet<Vertex*> visited;

    QHash<Vertex*, int> distanceFromStart;
    int infectedCounter = 0;

    queue.enqueue(startVertex);
    visited.insert(startVertex);
    distanceFromStart.insert(startVertex, 0);

    while (!queue.isEmpty()) {
        // find next vertex and its neighbors
        Vertex* currentVertex = queue.dequeue();
        QVector<Vertex*> neighbors = m_graph.values(currentVertex);

        // Logic
        if (currentVertex->getIsInfected())
            infectedCounter++;
        else {
            isSource = false;
            break;
        }

        int distance = distanceFromStart.value(currentVertex);
        if (distance >= m_data.getDays())
            continue;

        // add all unvisited neighbors to the queue
        for (Vertex* neighbor : neighbors) {
            if (!visited.contains(neighbor)) {
                queue.enqueue(neighbor);
                visited.insert(neighbor);
                distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
            }
        }
    }

    if (infectedCounter != m_data.getInfectedVertices().size())
        isSource = false;

    return isSource;
}
