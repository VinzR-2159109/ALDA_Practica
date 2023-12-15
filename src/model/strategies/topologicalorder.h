#ifndef TOPOLOGICALORDER_H
#define TOPOLOGICALORDER_H

#include "basestrategy.h"
#include "vertex.h"
#include <QMultiHash>
class topologicalOrder : public BaseStrategy
{
public:
    QVector<Vertex*> execute();
private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    QVector<Vertex*> orderTopologicly();
    void topologicalSortUtil(Vertex* vertex, QSet<Vertex*>& visited, QVector<Vertex*>& order);

    void createGraph();
    QVector<Vertex*> findSources();
    bool checkIfSource(Vertex* startVertex, const QSet<Vertex*>& infectedSet);
};

#endif // TOPOLOGICALORDER_H
