#ifndef MATRIXEXPONENTIATION_H
#define MATRIXEXPONENTIATION_H

#include <basestrategy.h>

class MatrixExponentiation : public BaseStrategy
{
public:
    QVector<Vertex *> execute() override;

private:
    QVector<QVector<int>> m_matrix;

    void createMatrix();
};

#endif // MATRIXEXPONENTIATION_H
