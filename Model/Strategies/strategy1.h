#ifndef STRATEGY1_H
#define STRATEGY1_H

#include <Model/basestrategy.h>

#include <QMultiHash>

class Strategy1 : public BaseStrategy
{
public:
    QVector<Vertex*> execute() override;

private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    void createGraph();
    QVector<Vertex*> findSources();
    bool checkIfSource(Vertex* startvertex);
};

#endif // STRATEGY1_H
