#include "matrixexponentiation.h"
#include <iostream>

QVector<Vertex *> MatrixExponentiation::execute()
{
    createMatrix();
    return {};
}

// Sources:
// https://www.geeksforgeeks.org/matrix-exponentiation/
// https://cp-algorithms.com/algebra/binary-exp.html
// https://cs.stackexchange.com/questions/1147/complexity-of-computing-matrix-powers
void MatrixExponentiation::createMatrix()
{
    int matrixSize = m_data->getVertices().size();

    // init matrix
    m_matrix = QVector<QVector<int>>(matrixSize);
    for (int i = 0; i < matrixSize; ++i) {
        m_matrix[i] = QVector<int>(matrixSize);
    }

    // add connections
    QHash<Vertex*, int> vertexIndexHash;
    QHash<int, Vertex*> indexVertexHash;

    int previousIndex = 0;
    for (auto it = m_data->getConnections().cbegin(); it != m_data->getConnections().cend(); it++) {

        // if new vertex -> place in index hash
        if (!vertexIndexHash.contains(it.key())) {
            vertexIndexHash.insert(it.key(), previousIndex);
            indexVertexHash.insert(previousIndex, it.key());
            previousIndex++;
        }

        // if new vertex -> place in index hash
        if (!vertexIndexHash.contains(it.value())) {
            vertexIndexHash.insert(it.value(), previousIndex);
            indexVertexHash.insert(previousIndex, it.value());
            previousIndex++;
        }

        int indexFrom = vertexIndexHash.value(it.key());
        int indexTo = vertexIndexHash.value(it.value());

        m_matrix[indexFrom][indexTo] = 1;
    }

    // Print the adjacency matrix
    std::cout << "   ";
    for (int j = 0; j < matrixSize; ++j) {
        std::cout << indexVertexHash.value(j)->getName().toStdString() << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < matrixSize; ++i) {
        std::cout << indexVertexHash.value(i)->getName().toStdString() << ": ";
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << m_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
