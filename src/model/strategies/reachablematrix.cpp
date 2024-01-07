#include "reachablematrix.h"
#include <bitset>
#include <iostream>

/**
 * Deze strategie werkt als volgt:
 *
 *  1. Maak een graph aan door alle connecties in een adjacency matrix te steken.
 *  2. Maak een 'reachable' matrix waarbij
 *      - 1 betekend dat vertex B bereikbaar is vanuit vertex A binnen het aantal dagen.
 *      - 0 betekend dat vertex B niet bereikbaar is vanuit vertex A binnen het aantal dagen.
 *  3. Bereken de waarde van de juiste oplossing
 *      - Bijvoorbeeld: Vertex A = besmet, B = niet besmet, C = besmet -> binair: 101 -> decimaal: 5
 *  4. Bereken de waarde van alle rijen van de 'reachable' matrix
 *      - Bijvoorbeeld:   A B C
 *                      A 1 0 0 :: -> 4
 *                      B 0 1 0 :: -> 2
 *                      C 0 0 1 :: -> 1
 *  5. Vind het kleinste aantal waardes dat samen de waarde van de juiste oplossing is.
 *      - 5 = 4 + 1 -> A en C zijn de oplossing
 *      In plaats van optellen gebruiken we de 'or' operator. Dit doen we omdat er edge cases zijn waarbij 2 of meer sources dezelfde vertex kunnen infecteren.
 *
 *  Nadelen van deze methode:
 *      1. Het vinden van het kleinste aantal waarden die samen de oplossing vormen heeft op dit moment een zeer slechte tijdscomplexiteit.
 *         Dit kan mischien later nog verbeterd worden.
 *
 *  Voordelen van deze methode:
 *      1. Onafhankelijk van het aantal edges
 *      2. Werkt voor alle edge cases
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

/**
 * Deze functie maakt de 'reachable' matrix aan vanuit de adjacency matrix. Door de adjacency matrix tot een macht 'x' te doen krijg je een matrix
 * waarin staat hoeveel routes er zijn van A naar B in exact x stappen. Als je zegt dat en vertex ook naar zijn eigen kan geen krijg je een matrix waarin staat
 * of een vertex een andere vertex kan bereiken in 'x' of minder dagen.
 *
 * De macht wordt berekend met behulp van 'binary exponentiation'. Hierdoor moeten er veel minder matrix berekeningen uitgevoerd worden.
 * Omdat het niet uitmaakt hoeveel verschillende routes er zijn van vertex A naar B wordt er verder gegaan naar de volgende connectie
 * zodra er één route gevonden is.
 *
 * Er zijn ook nog andere algoritmes om 2 matrixen met elkaar te vermenigvuldigen in O(n^2.37) tijd, maar deze zijn redelijk complex. Daarom hebben
 * we er voor gekozen om een gemakkelijke oplossing in O(n³) tijd te gebruiken.
 *
 * Tijdscomplexiteit: O(log(D) * (V³ + V²)) -> O(log(D) * V³) met D = aantal dagen en V = aantal vertices.
 */
void ReachableMatrix::createReachableMatrix(QVector<QVector<bool>> &adjacencyMatrix, QVector<QVector<bool>> &reachableMatrix, int days)
{
    int matrixSize = adjacencyMatrix.size();

    // Create a vector that can hold log(days) matrices of size VxV
    QVector<QVector<QVector<bool>>> results(std::floor(std::log2(days)) + 1, QVector<QVector<bool>>(matrixSize, QVector<bool>(matrixSize, false)));
    results[0] = adjacencyMatrix;

    // Bereken welke vertices elkaar kunnen bereiken binnen het aantal dagen -> O(log(D)) met D = aantal dagen)
    for (int count = 1; count < results.size(); count++) {
        multiplicateMatrix(results[count - 1], results[count - 1], results[count]);
    }

    // Calculate final array
    std::vector<bool> dayBinary;
    while (days > 0) {
        dayBinary.push_back(days % 2);
        days /= 2;
    }

    int flag = false;
    for (int count = 0; count < results.size(); count++) {
        if (dayBinary[count] == 0) {
            continue;
        }

        if (flag == false){
            reachableMatrix = results[count];
            flag = true;
        }
        else {
            multiplicateMatrix(reachableMatrix, results[count], reachableMatrix);
        }
    }
}

/**
 * Deze functie vind het kleinste vertices die nodig zijn om alle geïnfecteerde vertices te infecteren.
 *
 * Dit wordt gedaan door de waarde van de oplossing te berekenen. Dit wordt berekend als volgt:
 *      Besmet, Niet besmet, besmet -> 1 0 1 (binair) -> 5 (decimaal)
 *
 * Hetzelfde wordt gedaan voor elke rij in de matrix. De oplossing moet, wanneer deze bij elkaar wordt gezet met een 'or' operator, de waarde van de oplossing zijn.
 * En dit door zo weinig mogelijk rijen te gebruiken.
 *
 * Door tijdsgebrek brute forcen we de oplossing door elke mogelijke combinatie te bekijken. Door gebruik te maken van een backtrack algoritme kan dit wel
 * verbeterd worden. Als dit algoritme een oplossing vind van bijvoorbeeld 3 rijen, hoeven de combinaties van 3 of meer rijen niet meer bekeken te worden.
 * Deze gaan namelijk nooit beter zijn dan de huidige oplossing. Daarnaast kan er al vroeger gestopt worden zodra de waarde van de gecombineerde rijen groter is dan
 * de uitkomst, geen enkele verdere combinatie gaat de uitkomst geven omdat de waarde enkel groter kan worden.
 *
 * Tijdscomplexiteit: O(V + V² + 2^V) -> O(2^V) met V = aantal vertices.
 */
QVector<Vertex*> ReachableMatrix::findSources(QVector<QVector<bool>> &reachableMatrix)
{
    // Bereken de waarde die de oplossing moet hebben -> O(V)
    int targetValue = 0;
    for (const auto &vertex : m_data->getVertices()) {
        int index = m_vertexIndexHash.value(vertex);
        targetValue += std::pow(2, index) * vertex->getIsInfected();
    }

    // Bereken de waarde van elke rij -> O(V²)
    QVector<int> rowValues;
    for (const auto &row : reachableMatrix) {
        int value = 0;
        for (int i = 0; i < row.size(); ++i) {
            value += std::pow(2, i) * row[i];
        }
        rowValues.push_back(value);
    }

    // Vind een combinatie van rijen die samen de waarde van de oplossingen hebben, en dit met zo weinig mogelijk rijen.
    // Brute force -> O(2^V)
    QVector<Vertex*> solution;
    int maxCombinations = 1 << m_data->getInfectedVertices().size(); // = 2^V combinations
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

/**
 * Deze functie vermenigvuldigd 2 matrices met elkaar. Dit heeft een tijdscomplexiteit van O(V³).
 * Er zijn ook nog andere algoritmes om 2 matrixen met elkaar te vermenigvuldigen in O(n^2.37) tijd, maar deze zijn redelijk complex. Daarom hebben
 * we er voor gekozen om een gemakkelijke oplossing in O(n³) tijd te gebruiken.
 *
 * Tijdscomplexiteit: O(V³) met V = aantal vertices.
 */
void ReachableMatrix::multiplicateMatrix(QVector<QVector<bool> > &matrix1, QVector<QVector<bool> > &matrix2, QVector<QVector<bool> > &result)
{
    int matrixSize = matrix1.size();

    QVector<QVector<bool>> tempResult = QVector<QVector<bool>>(matrixSize, QVector<bool>(matrixSize, false));

    // Matrix multiplicatie -> (O(V³) met V = aantal vertices)
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            for (int k = 0; k < matrixSize; k++) {
                if (matrix1[i][k] && matrix2[k][j]) {
                    tempResult[i][j] = 1;
                    break;
                }
            }
        }
    }

    result = tempResult;
}
