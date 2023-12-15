#ifndef BFSSEPERATE_H
#define BFSSEPERATE_H

#include <basestrategy.h>

class BFSSeperate : public BaseStrategy
{
public:
    QVector<Vertex*> execute() override;

private:
    QMultiHash<Vertex*, Vertex*> m_graph;

    QVector<Vertex*> findSources();
    void addIfRule1(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex);
    void removeIfNotRule2(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex);
    void removeIfNotRule3(QSet<Vertex*> &sources, QSet<Vertex*> &infectedByVertex);
};

#endif // BFSSEPERATE_H
