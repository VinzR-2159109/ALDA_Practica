#include "bfs.h"

#include <QHash>
#include <QQueue>
#include <QSet>
#include <iostream>

/**
 * Deze strategie werkt als volgt:
 *
 *  1. Maak een graph aan door alle connecties in een QMultiHash te steken.
 *  2. Vind alle mogelijke sources
 *      - Loop door alle vertices
 *      - Voor elke vertex, voer een breath first search algoritme uit om te controleren of de volgende voorwaarden voldaan worden:
 *          Regel 1: Alle vertices die op <= verlopen dagen bereikt worden moeten besmet zijn
 *          Regel 2: Alle vertices die op het aantal verlopen dagen + 1 dagen bereikt worden moeten niet besmet zijn
 *          Regel 3: Alle vertices die geïnfecteerd zijn door een andere vertex kunnen niet de source zijn
 *
 *  Nadelen van deze methode:
 *      1. Kan niet overweg met de edge case 'infected_vertex_out_of_range'
 *
 *  Voordelen van deze methode:
 *      1. Redelijk lage tijdscomplexiteit in vergelijking met onze andere methodes (O(V² + VE))
 *         Dit is goed als er niet veel meer edges zijn dan vertices. Zodra er zeer veel edges zijn kan het zijn dat de matrix oplossing beter is.
 */
QVector<Vertex*> BFS::execute()
{
    if (!m_data)
        return {};

    m_graph = m_data->getConnections();
    return findSources();
}

/**
 * Voert de checkIfSource() functie uit voor elke geïnfecteerde vertex.
 * checkIfSource() heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 *
 * Tijdscomplexiteit: O(I * (V + E)) met I = aantal geïnfecteerde vertices, V = aantal vertices, E = aantal edges
 * Worst case I = V -> O(V * (V + E)) -> O(V² + VE)
 */
QVector<Vertex*> BFS::findSources()
{
    QSet<Vertex*> sources;
    QSet<Vertex*> infectedByVertex;

    for (const auto &vertex : m_data->getInfectedVertices()) {
        addIfSource(vertex, sources, infectedByVertex);
    }

    return QVector<Vertex*>(sources.begin(), sources.end());
}

/**
 * Deze functie controleerd of de gegeven vertex een source kan zijn en voegt deze toe aan een lijst indien dit zo is.
 * Dit is een breadth first search algoritme, deze heeft een tijdscomplexiteit van O(V + E) met V het aantal vertices en E het aantal edges.
 * Als de vertex geen source kan zijn returnt de functie, hierdoor wordt er vaak niet naar elke vertex in de graph gekeken (early return).
 * Daarnaast worden enkel de vertices bekeken die bereikbaar zijn in het aantal dagen dat is meegegeven in de data + 1. In het slechte geval is dit
 * gelijk aan alle vertices.
 *
 * Als de vertex een source kan zijn worden alle vertices die de startVertex heeft geïnfecteer verwijderd van de mogelijk oplossing.
 * Zo wordt de kleinst mogelijke oplossing bekomen.
 *
 * Tijdscomplexiteit: O(V + E + I) met V = aantal vertices, E = aantal edges en I = aantal geïnfecteerde vertices
 * worst case I = V -> O(2V + E) -> O(V + E)
 */
void BFS::addIfSource(Vertex* startVertex, QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex)
{
    // Controleer of de vertex al is geïnfecteerd door een andere vertex (Regel 3) -> O(1)
    if (infectedByVertex.contains(startVertex))
        return;

    // Breadth first search -> O(V + E)
    QQueue<Vertex*> queue;
    QHash<Vertex*, int> distanceFromStart; // Dient ook als visited

    queue.enqueue(startVertex);
    distanceFromStart.insert(startVertex, 0);

    while (!queue.isEmpty()) {
        Vertex* currentVertex = queue.dequeue();

        // Controleer of de vertex voldoet aan regel 1 & 2
        if (distanceFromStart.value(currentVertex) <= m_data->getDays()) {
            if (!currentVertex->getIsInfected())
                return;
        }
        else if (distanceFromStart.value(currentVertex) == m_data->getDays() + 1){
            if (currentVertex->getIsInfected() && !infectedByVertex.contains(currentVertex))
                return;
        }
        else {
            continue;
        }

        QVector<Vertex*> neighbors = m_graph.values(currentVertex);
        for (Vertex* neighbor : neighbors) {
            if (!distanceFromStart.contains(neighbor)) {
                queue.enqueue(neighbor);
                distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
            }
        }
    }

    // Zorg dat regel 3 voldaan wordt -> O(I) met I = aantal bekeken vertices (worst case alle geïnfecteerde vertices)
    for (auto it = distanceFromStart.cbegin(); it != distanceFromStart.cend(); it++) {
        if (sources.contains(it.key())) {
            sources.remove(it.key());
        }

        infectedByVertex.insert(it.key());
    }

    sources.insert(startVertex);
}
