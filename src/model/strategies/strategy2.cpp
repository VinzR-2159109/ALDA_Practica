#include "strategy2.h"

#include <QQueue>
#include <QSet>

/*
 * Het idee is om verschillende lijsten te maken en op basis van de inhoud daarvan de sources te kiezen
 *
 * We maken een lijst van:
 *      - Alle vertices die voldoen aan Regel 1
 *      - Alle vertices die voldoen aan Regel 2
 *      - Alle vertices die een bepaalde vertex kunnen besmetten, en dit voor elke besmette vertex
 *
 * Op basis hiervan kunnen we de source vinden:
 *      - We loopen door alle besmette vetices:
 *          - Vertex moet in lijst voor regel 1 staan
 *          - Vertex moet in lijst voor regel 2 staan
 *          - Vertex moet in zo veel mogelijk 'besmet door' lijsten staan
 *          - ...
 */

QVector<Vertex *> Strategy2::execute()
{
    QMultiHash<Vertex*, Vertex*> graph = m_data->getConnections();
    QSet<Vertex*> sources;

    addIfOnlyInfectedInRange(graph, sources);

    return QVector<Vertex*>(sources.begin(), sources.end());
}

void Strategy2::addIfOnlyInfectedInRange(QMultiHash<Vertex*, Vertex*> &graph, QSet<Vertex*> &sources)
{
    for (const auto &vertex : m_data->getInfectedVertices()) {

        QQueue<Vertex*> queue;
        QHash<Vertex*, int> distanceFromStart; // Dient ook als visited

        queue.enqueue(vertex);
        distanceFromStart.insert(vertex, 0);

        while (!queue.isEmpty()) {
            Vertex* currentVertex = queue.dequeue();

            if (distanceFromStart.value(currentVertex) <= m_data->getDays()) {
                if (!currentVertex->getIsInfected())
                    return;
            }

            QVector<Vertex*> neighbors = graph.values(currentVertex);
            for (Vertex* neighbor : neighbors) {
                if (!distanceFromStart.contains(neighbor)) {
                    queue.enqueue(neighbor);
                    distanceFromStart.insert(neighbor, distanceFromStart.value(currentVertex) + 1);
                }
            }
        }

        sources.insert(vertex);
    }
}

void Strategy2::infectedBy(QMultiHash<Vertex *, Vertex *> graph, QSet<Vertex *> &sources)
{

}
