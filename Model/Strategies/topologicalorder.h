#ifndef TOPOLOGICALORDER_H
#define TOPOLOGICALORDER_H


#include "Model/basestrategy.h"
#include "Model/vertex.h"
#include <QMultiHash>
class topologicalOrder : public BaseStrategy
{
public:
    QVector<Vertex*> execute() override;
private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    QVector<Vertex*> orderTopologicly();
    void topologicalSortUtil(Vertex* vertex, QSet<Vertex*>& visited, QVector<Vertex*>& order);

    void createGraph();
    QVector<Vertex*> findSources();
    bool checkIfSource(Vertex* startVertex, const QSet<Vertex*>& infectedSet);
};

#endif // TOPOLOGICALORDER_H
