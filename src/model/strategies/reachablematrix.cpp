#include "reachablematrix.h"
#include <iostream>

/**
 * Deze strategie werkt als volgt:
 *
 *  1. Maak een graph aan door alle connecties in een adjacency matrix te steken.
 *  2. Maak een 'reachable' matrix waarbij
 *      - 1 betekend dat vertex B bereikbaar is vanuit vertex A binnen het aantal dagen.
 *      - 0 betekend dat vertex B niet bereikbaar is vanuit vertex A binnen het aantal dagen.
 *  3. Bereken de decimale waarde van de juiste oplossing
 *      - Bijvoorbeeld: Vertex A = besmet, B = niet besmet, C = besmet -> 101 -> 5
 *  4. Bereken de decimale waarde van alle rijen van de 'reachable' matrix
 *      - Bijvoorbeeld:   A B C
 *                      A 1 0 0 :: -> 4
 *                      B 0 1 0 :: -> 2
 *                      C 0 0 1 :: -> 1
 *  5. Vind het kleinste aantal waardes dat samen de waarde van de juiste oplossing is
 *      - 5 = 4 + 1 -> A en C zijn de oplossing
 *
 *  Nadelen van deze methode:
 *      1. /
 *
 *  Voordelen van deze methode:
 *      1. Onafhankelijk van het aantal edges
 */
QVector<Vertex *> ReachableMatrix::execute()
{
    int matrixSize = m_data->getVertices().size();

    QVector<QVector<bool>> adjacencyMatrix = QVector<QVector<bool>>(matrixSize);
    QVector<QVector<bool>> reachableMatrix;

    // Init adjacencyMatrix
    for (int i = 0; i < matrixSize; ++i) {
        adjacencyMatrix[i] = QVector<bool>(matrixSize);
    }

    createAdjacencyMatrix(adjacencyMatrix);
    createReachableMatrix(adjacencyMatrix, reachableMatrix, m_data->getDays());

    // FOR TESTING --------------------
    printMatrix(reachableMatrix);

    std::cout << "Target value: ";
    int targetValue = 0;
    for (const auto &vertex : m_data->getVertices()) {
        int index = m_vertexIndexHash.value(vertex);
        targetValue += std::pow(2, reachableMatrix.size() - 1 - index) * vertex->getIsInfected();
        std::cout << vertex->getIsInfected() << " ";
    }
    std::cout << ":: " << targetValue << "\n";
    // --------------------------------

    return findSources(reachableMatrix);
}

void ReachableMatrix::createAdjacencyMatrix(QVector<QVector<bool>> &adjacencyMatrix)
{
    int previousIndex = 0;
    for (const auto &vertex : m_data->getVertices()) {
        m_vertexIndexHash.insert(vertex, previousIndex);
        m_indexVertexHash.insert(previousIndex, vertex);

        adjacencyMatrix[previousIndex][previousIndex] = 1;

        previousIndex++;
    }

    for (auto it = m_data->getConnections().cbegin(); it != m_data->getConnections().cend(); it++) {
        int indexFrom = m_vertexIndexHash.value(it.key());
        int indexTo = m_vertexIndexHash.value(it.value());

        adjacencyMatrix[indexFrom][indexTo] = 1;
    }
}

void ReachableMatrix::createReachableMatrix(QVector<QVector<bool>> &adjacencyMatrix, QVector<QVector<bool>> &reachableMatrix, int days)
{
    reachableMatrix = adjacencyMatrix;

    QVector<QVector<bool>> m1 = adjacencyMatrix;
    QVector<QVector<bool>> m2 = adjacencyMatrix;

    QVector<QVector<bool>> *previousResult = &m1;
    QVector<QVector<bool>> *temp = &m2;

    int matrixSize = adjacencyMatrix.size();

    // Bereken welke vertices elkaar kunnen bereiken binnen het aantal dagen
    for (int day = 0; day < days - 1; day++) {

        // Matrix multiplicatie
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                (*temp)[i][j] = 0;
                for (int k = 0; k < matrixSize; k++) {
                    if ((*previousResult)[i][k] * adjacencyMatrix[k][j] == 1) {
                        (*temp)[i][j] = 1;
                    }
                }
            }
        }

        // Set temp in previousResult (switch pointers)
        QVector<QVector<bool>> *pointer = previousResult;
        previousResult = temp;
        temp = pointer;

        // Update reachableMatrix
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                reachableMatrix[i][j] += (*previousResult)[i][j];
            }
        }
    }
}

QVector<Vertex*> ReachableMatrix::findSources(QVector<QVector<bool>> &reachableMatrix)
{
    // Bereken de waarde die de oplossing moet hebben
    int targetValue = 0;
    for (const auto &vertex : m_data->getVertices()) {
        int index = m_vertexIndexHash.value(vertex);
        targetValue += std::pow(2, index) * vertex->getIsInfected();
    }

    // Bereken de waarde van elke rij
    QVector<int> rowValues;
    for (const auto &row : reachableMatrix) {
        int value = 0;
        for (int i = 0; i < row.size(); ++i) {
            value += std::pow(2, i) * row[i];
        }
        rowValues.push_back(value);
    }

    // Vind een combinatie van rijen die samen de waarde van de oplossingen hebben, en dit met zo weinig mogelijk rijen.

    // Mogelijke oplossingen:
    //      - Alle combinaties maken en de kleinste eruit halen -> O(I!) = niet doenbaar
    //      - Backtracking?

    // Voor nu brute force:
    QVector<Vertex*> solution;
    int maxCombinations = 1 << m_data->getInfectedVertices().size(); // = 2^n combinations
    for (int i = 1; i < maxCombinations; ++i) {
        int value = i;
        QVector<Vertex*> possibleSolution;
        int combinationValue = 0;

        for (const auto &vertex : m_data->getInfectedVertices()) {

            if (value % 2) {
                possibleSolution.push_back(vertex);
                combinationValue |= rowValues[m_vertexIndexHash.value(vertex)];
            }

            value /= 2;
            if (value == 0)
                break;
        }

        if (combinationValue == targetValue && (possibleSolution.size() < solution.size() || solution.empty())) {
            solution = possibleSolution;
        }
    }

    return solution;
}

// FOR TESTING
void ReachableMatrix::printMatrix(QVector<QVector<bool>> &matrix)
{
    int matrixSize = matrix.size();

    std::cout << "   ";
    for (int j = 0; j < matrixSize; ++j) {
        std::cout << m_indexVertexHash.value(j)->getName().toStdString() << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < matrixSize; ++i) {
        std::cout << m_indexVertexHash.value(i)->getName().toStdString() << ": ";
        for (int j = 0; j < matrixSize; ++j) {
            std::cout << matrix[i][j] << " ";
        }

        // calculate decimal value
        int value = 0;
        for (int j = 0; j < matrixSize; ++j) {
            value += std::pow(2, matrixSize - 1 - j) * matrix[i][j];
        }

        std::cout << ":: " << value << "\n";
    }
    std::cout << "\n";
}
