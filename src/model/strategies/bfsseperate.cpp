#include "bfsseperate.h"

#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

/**
 * Deze strategie werkt als volgt:
 *
 *  1. Maak een graph aan door alle connecties in een QMultiHash te steken.
 *  2. Vind alle mogelijke sources
 *      - Voeg alle vertices toe aan sources die voldoen aan regel 1
 *      - verwijder alle vertices in de sources lijst die niet voldoen aan regel 2
 *      - verwijder alle vertices in de sources lijst die niet voldien aan regel 3
 *
 *  Regel 1: Alle vertices die op <= verlopen dagen bereikt worden moeten besmet zijn
 *  Regel 2: Alle vertices die op >  verlopen dagen bereikt worden moeten niet besmet zijn of besmet zijn door een andere vertex
 *  Regel 3: Alle vertices die geïnfecteerd zijn door een andere kunnen niet de source zijn
 *
 *  Nadelen van deze methode:
 *      1. /
 *
 *  Voordelen van deze methode:
 *      1. /
 */
QVector<Vertex*> BFSSeperate::execute()
{
    if (!m_data)
        return {};

    m_graph = m_data->getConnections();
    return findSources();
}

/**
 * TODO
 *
 *
 * Tijdscomplexiteit:
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
QVector<Vertex*> BFSSeperate::findSources()
{
    QSet<Vertex*> sources;
    QSet<Vertex*> infectedByVertex;

    addIfRule1(sources, infectedByVertex);
    removeIfNotRule2(sources, infectedByVertex);
    removeIfNotRule3(sources, infectedByVertex);

    return QVector<Vertex*>(sources.begin(), sources.end());
}

/**
 * Deze functie voegt alle vertices toe die voldoen aan regel 1.
 * Dit is een breadth first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 * Als de vertex geen source kan zijn wordt er niet verder gekeken, hierdoor wordt er vaak niet naar elke vertex in de graph gekeken (early return).
 *
 * Tijdscomplexiteit: O(V + E + I) met V = aantal vertices, E = aantal edges en I = aantal geïnfecteerde vertices
 * worst case I = V -> O(2V + E) -> O(V + E)
 *
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
void BFSSeperate::addIfRule1(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex)
{
    for (int i = 0; i < m_data->getInfectedVertices().size(); i++) {
        Vertex* startVertex = m_data->getInfectedVertices()[i];

        // Controleer of de vertex al is geïnfecteerd door een andere vertex (Regel 3) -> O(1)
        if (infectedByVertex.contains(startVertex))
            return;

        QQueue<Vertex*> queue;
        QHash<Vertex*, int> distanceFromStart; // Dient ook als visited

        queue.enqueue(startVertex);
        distanceFromStart.insert(startVertex, 0);

        while (!queue.isEmpty()) {
            Vertex* currentVertex = queue.dequeue();

            if (distanceFromStart.value(currentVertex) <= m_data->getDays()) {
                if (!currentVertex->getIsInfected())
                    goto outerloop;
            }

            QVector<Vertex*> neighbors = m_graph.values(currentVertex);
            for (Vertex* neighbor : neighbors) {
                if (!distanceFromStart.contains(neighbor)) {
                    queue.enqueue(neighbor);
                    distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
                }
            }
        }

        for (auto it = distanceFromStart.cbegin(); it != distanceFromStart.cend(); it++) {
            infectedByVertex.insert(it.key());
        }

        sources.insert(startVertex);

    outerloop:;
    }
}

/**
 * Deze functie verwijderd alle vertices toe die niet voldoen aan regel 2.
 * Dit is een breadth first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 * Als de vertex geen source kan zijn wordt er niet verder gekeken, hierdoor wordt er vaak niet naar elke vertex in de graph gekeken (early return).
 *
 * Tijdscomplexiteit: O(V + E + S) met V = aantal vertices, E = aantal edges en S = aantal potentiële sources
 * worst case S = V -> O(2V + E) -> O(V + E)
 *
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
void BFSSeperate::removeIfNotRule2(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex)
{
    for (const auto &source : sources) {
        QQueue<Vertex*> queue;
        QHash<Vertex*, int> distanceFromStart; // Dient ook als visited

        queue.enqueue(source);
        distanceFromStart.insert(source, 0);
        while (!queue.isEmpty()) {
            Vertex* currentVertex = queue.dequeue();

            // Controleer of de vertex voldoet aan regel 1 & 2
            if (distanceFromStart.value(currentVertex) > m_data->getDays()) {
                if (!currentVertex->getIsInfected() && !infectedByVertex.contains(currentVertex)) {
                    sources.remove(currentVertex);
                    goto outerloop;
                }
            }

            QVector<Vertex*> neighbors = m_graph.values(currentVertex);
            for (Vertex* neighbor : neighbors) {
                if (!distanceFromStart.contains(neighbor)) {
                    queue.enqueue(neighbor);
                    distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
                }
            }
        }

    outerloop:;
    }
}

/**
 * Deze functie verwijderd alle vertices toe die niet voldoen aan regel 3.
 * Dit is een breadth first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 * Als de vertex geen source kan zijn wordt er niet verder gekeken, hierdoor wordt er vaak niet naar elke vertex in de graph gekeken (early return).
 *
 * Tijdscomplexiteit: O(S) met S = aantal potentiële sources
 * worst case S = V -> O(V)
 *
 * Ruimtecomplexiteit:
 * Auxiliary space:
 */
void BFSSeperate::removeIfNotRule3(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex)
{
    for (const auto &source : sources) {
        if (infectedByVertex.contains(source)) {
            sources.remove(source);
        }
    }
}
