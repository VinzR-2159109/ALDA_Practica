#ifndef STRATEGY1_H
#define STRATEGY1_H

#include "basestrategy.h"

#include <QMultiHash>
#include <QSet>

class Strategy1 : public BaseStrategy
{

public:
    QVector<Vertex*> execute() override;

private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    QVector<Vertex*> findSources();
    void addIfSource(Vertex* startvertex, QVector<Vertex*> &sources, QSet<Vertex*> &infectedVertex);
};

#endif // STRATEGY1_H
