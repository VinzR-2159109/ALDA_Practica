#ifndef STRATEGY2_H
#define STRATEGY2_H

#include <basestrategy.h>

class Strategy2 : public BaseStrategy
{
public:
    QVector<Vertex *> execute();

private:
    void addIfOnlyInfectedInRange(QMultiHash<Vertex*, Vertex*> &graph, QSet<Vertex*> &sources);
    void infectedBy(QMultiHash<Vertex*, Vertex*> graph, QSet<Vertex*> &sources);
};

#endif // STRATEGY2_H
