#include "strategy1.h"

#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

/**
 * Deze strategie werkt als volgt:
 *
 *  1. Maak een graph aan door alle connecties in een QMultiHash te steken.
 *  2. Vind alle mogelijke sources
 *      a. Loop door alle vertices
 *      b. Voor elke vertex, doe een breath first search algoritme om te controleren of de volgende voorwaarden voldaan worden:
 *          - Alle vertices die op <= verlopen dagen bereikt worden moeten besmet zijn
 *          - Alle vertices die op >  verlopen dagen bereikt worden moeten niet besmet zijn
 *
 *  Nadelen van deze methode:
 *      1. Slechte tijdscomplexiteit: O(V * (V + E)) -> O(V² + V * E) -> groteorde O(V²)
 *      2. Returned alle mogelijke sources, niet de kleinst mogelijke subset
 *
 *  Voordelen van deze methode:
 *      1. /
 */
QVector<Vertex*> Strategy1::execute()
{
    createGraph();
    return findSources();
}

/**
 * Deze functie mpaakt de graph aan door over alle connecties te lopen en deze in een QMultiHash te steken.
 *
 * Tijdscomplexiteit: O(E) met E = aantal edges
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
void Strategy1::createGraph()
{
    for (const auto &connection : m_data.getConnections()) {
        m_graph.insert(connection.first, connection.second);
    }
}

/**
 * Voert de checkIfSource() functie uit voor elke vertex.
 * checkIfSource() is een breath first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 *
 * Tijdscomplexiteit: O(V * (V + E)) met V = aantal vertices, E = aantal edges
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
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

/**
 * Deze functie controleerd of de gegeven vertex een source kan zijn.
 * Dit is een breath first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 * Als de vertex geen source kan zijn returnt de functie 'false', hierdoor wordt er vaak niet naar elke vertex gekeken (early return).
 *
 * Tijdscomplexiteit: O(V + E) met V = aantal vertices, E = aantal edges
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
bool Strategy1::checkIfSource(Vertex* startVertex)
{
    QQueue<Vertex*> queue;
    QHash<Vertex*, int> distanceFromStart; // Dient ook als visited

    queue.enqueue(startVertex);
    distanceFromStart.insert(startVertex, 0);

    while (!queue.isEmpty()) {
        Vertex* currentVertex = queue.dequeue();

        // Logic
        if (distanceFromStart.value(currentVertex) <= m_data.getDays()) {
            if (!currentVertex->getIsInfected())
                return false;
        }
        else {
            if (currentVertex->getIsInfected())
                return false;
        }

        // add all unvisited neighbors to the queue
        QVector<Vertex*> neighbors = m_graph.values(currentVertex);
        for (Vertex* neighbor : neighbors) {
            if (!distanceFromStart.contains(neighbor)) {
                queue.enqueue(neighbor);
                distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
            }
        }
    }

    return true;
}
