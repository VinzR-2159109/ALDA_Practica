#ifndef REACHABLEMATRIX_H
#define REACHABLEMATRIX_H

#include <basestrategy.h>

class ReachableMatrix : public BaseStrategy
{
public:
    QVector<Vertex *> execute() override;

private:
    QVector<QVector<int>> m_matrix;

    void createMatrix();
};

#endif // REACHABLEMATRIX_H
