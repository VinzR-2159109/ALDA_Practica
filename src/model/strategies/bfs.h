#ifndef BFS_H
#define BFS_H

#include "basestrategy.h"

#include <QMultiHash>
#include <QSet>

class BFS : public BaseStrategy
{

public:
    QVector<Vertex*> execute() override;

private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    QVector<Vertex*> findSources();
    void addIfSource(Vertex* startvertex, QSet<Vertex*> &sources, QSet<Vertex*> &infectedVertex);
};

#endif // BFS_H
