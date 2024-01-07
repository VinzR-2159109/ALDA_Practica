#ifndef REACHEBLEMATRIX_H
#define REACHEBLEMATRIX_H

#include <basestrategy.h>

class ReachableMatrix : public BaseStrategy
{
public:
    QVector<Vertex *> execute() override;

private:
    QHash<Vertex*, int> m_vertexIndexHash;
    QHash<int, Vertex*> m_indexVertexHash;

    void createAdjacencyMatrix(QVector<QVector<bool>> &adjacencyMatrix);
    void createReachableMatrix(QVector<QVector<bool>> &adjacencyMatrix, QVector<QVector<bool>> &reachableMatrix, int days);
    QVector<Vertex*> findSources(QVector<QVector<bool>> &reachableMatrix);
    QVector<int> findMinRows();

    void multiplicateMatrix(QVector<QVector<bool>> &matrix1, QVector<QVector<bool>> &matrix2, QVector<QVector<bool>> &result);
};

#endif // REACHEBLEMATRIX_H
