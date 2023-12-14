#ifndef MATRIXEXPONENTIATION_H
#define MATRIXEXPONENTIATION_H

#include <basestrategy.h>

class MatrixExponentiation : public BaseStrategy
{
public:
    QVector<Vertex *> execute() override;

private:
    QHash<Vertex*, int> m_vertexIndexHash;
    QHash<int, Vertex*> m_indexVertexHash;

    void createAdjacencyMatrix(QVector<QVector<bool>> &adjacencyMatrix);
    void createReachableMatrix(QVector<QVector<bool>> &adjacencyMatrix, QVector<QVector<bool>> &reachableMatrix, int days);
    QVector<Vertex*> findSources(QVector<QVector<bool>> &reachableMatrix);

    void printMatrix(QVector<QVector<bool>> &matrix);
};

#endif // MATRIXEXPONENTIATION_H
