#include "topologicalorder.h"
#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

/*
 * De strategy toplogoicalOrdering werkt enkel bij deze specifieke gevallen:
 *     - De graph moet een Directed Acyclic Graph zijn.
 *       een cyclische graph omzetten naar een DAG is mogelijk: https://youtu.be/OQ5jsbhAv_M?si=fBx3TA76WgodV1zc&t=2816, maar redelijk complex
 *     - De ziekte moet zich in pad verspreiden.
 *     - Er moet exact één source zijn.
 *
 * Deze specifieke voorwaarden zijn niet bij alle mogelijke cases van toepassen, toch is het intressant om de tijdcomplexiteit van deze strategy te bekijken.
 *     - Toplogogisch sorteren van een DAG = O(V + E) met V #vertices en E #edges
 *     - Door de toplogogisch gesorteerde lijst gaan is O(V) met V #vertices
 *     - Totale tijdcomplexiteit is dus O( (V+E) * V), dit is dezelfde als strategy 1 (bfs). Waardoor deze de voorkeur krijgt.
 */


QVector<Vertex*> topologicalOrder::execute()
{
    m_graph = m_data->getConnections();
    return findSources();
}

/*
 * Alle vertices worden afgegaan en topologisch gesorteerd.
 * Voor elke vertex V wordt toplogoicalSortUtil gebruikt die zich recursief voor elke edge E van vertex V oproept
 * O(V + E)
 */
QVector<Vertex*> topologicalOrder::orderTopologicly()
{
    QVector<Vertex*> order;
    QSet<Vertex*> visited;

    // O(V) met V #vertices
    for (const auto &vertex : m_data->getVertices()) {
        if (!visited.contains(vertex)) { //Visited is QSet -> O(1)
            topologicalSortUtil(vertex, visited, order);
        }
    }

    return order;
}

void topologicalOrder::topologicalSortUtil(Vertex* vertex, QSet<Vertex*>& visited, QVector<Vertex*>& order)
{
    visited.insert(vertex);

    QVector<Vertex*> neighbors = m_graph.values(vertex);
    // O(E) met E #edges
    for (Vertex* neighbor : neighbors) {
        if (!visited.contains(neighbor)) {
            topologicalSortUtil(neighbor, visited, order);
        }
    }

    order.prepend(vertex);
}

/*
 * Ervan uitgaand dat de ziekte zich verspreid vanuit één source.
 * Aangezien dat de eerste geïnfecteerde vertex voor alle andere geïnfecteerde vertices komen.
 * Moet deze eerste vertex de source zijn.
 *
 * Dit werkt enkel als je ervan uit kan gaan dat de ziekte zich vanuit één source verspreidt.
 */
QVector<Vertex*> topologicalOrder::findSources()
{
    QVector<Vertex*> sources;
    QVector<Vertex*> topOrder = orderTopologicly();

    for (auto vertex : topOrder){
        if (vertex->getIsInfected()){
            sources.append(vertex);
            return sources;
        }
    }

    return {};
}


