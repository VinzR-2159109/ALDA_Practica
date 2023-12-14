#include "topologicalorder.h"
#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

QVector<Vertex*> topologicalOrder::execute()
{
    createGraph();
    return findSources();
}


void topologicalOrder::createGraph()
{
    for (const auto &connection : m_data.getConnections()) {
        m_graph.insert(connection.first, connection.second);
    }
}

/*
 * Alle vertices worden afgegaan en topologisch gesorteerd.
 */
QVector<Vertex*> topologicalOrder::orderTopologicly()
{
    QVector<Vertex*> order;
    QSet<Vertex*> visited;

    for (const auto &vertex : m_data.getVertices()) {
        if (!visited.contains(vertex)) {
            topologicalSortUtil(vertex, visited, order);
        }
    }

    return order;
}
/*
 * Diepste neighbor wordt gezocht en vooraan in order gestoken.
 *
*/
void topologicalOrder::topologicalSortUtil(Vertex* vertex, QSet<Vertex*>& visited, QVector<Vertex*>& order)
{
    visited.insert(vertex);

    QVector<Vertex*> neighbors = m_graph.values(vertex);
    for (Vertex* neighbor : neighbors) {
        if (!visited.contains(neighbor)) {
            topologicalSortUtil(neighbor, visited, order);
        }
    }

    order.prepend(vertex);
}

QVector<Vertex*> topologicalOrder::findSources()
{
    QVector<Vertex*> sources;
    QVector<Vertex*> topOrder = orderTopologicly();

    int maxDays = m_data.getDays();

    // Start with the last infected vertex in the topological order
    for (int i = topOrder.size() - 1; i >= 0; --i) {
        Vertex* lastInfected = topOrder[i];

        // Check if the vertex is infected
        if (lastInfected->getIsInfected()) {
            int daysCounter = 0;
            Vertex* currentVertex = lastInfected;

            // Trace back to find the source
            while (daysCounter < maxDays && currentVertex != nullptr) {
                QVector<Vertex*> neighbors = m_graph.values(currentVertex);
                Vertex* potentialSource = nullptr;

                // terug kunnen gaan?
                for (Vertex* neighbor : neighbors) {
                    // Check if the neighbor is infected
                    if (neighbor->getIsInfected()) {
                        potentialSource = neighbor;
                        break;
                    }
                }

                // Move to the potential source for the next iteration
                currentVertex = potentialSource;

                // Increment the days counter
                ++daysCounter;
            }

            // If the loop exited because of reaching the maximum days and not a null vertex, add the source
            if (daysCounter == maxDays && currentVertex == nullptr) {
                sources.push_back(lastInfected);
            }
        }
    }

    return sources;
}


