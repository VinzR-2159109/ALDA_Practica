#include "repository.h"

#include <QFile>

Repository::Repository()
{

}

Repository::Data Repository::LoadFile(QString filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    Data data = Data();

    if (file.isOpen()) {
        QString line = "";

        // Load all vertices
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList vertexNames = line.split(',');
            for (const auto &name : vertexNames) {

                for (const auto vertex : data.vertices) {
                    if (vertex->getName() == name) {
                        data.loadSucces = false;
                        return data;
                    }
                }

                data.vertices.push_back(new Vertex(name));
            }
        }

        // Load connections
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList connectionStrings = line.split(',');
            for (const auto &connectionString : connectionStrings) {
                QStringList vertexNames = connectionString.split("->");

                Vertex *vertex1, *vertex2;
                for (const auto vertex : data.vertices) {
                    if (vertex->getName() == vertexNames[0])
                        vertex1 = vertex;

                    if (vertex->getName() == vertexNames[1])
                        vertex2 = vertex;
                }

                data.connections.push_back(std::make_pair(vertex1, vertex2));
            }
        }

        // Load infected vertices
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList infectedVertexNames = line.split(',');
            for (const auto &infectedVertexName : infectedVertexNames) {
                Vertex *vertex;
                for (const auto v : data.vertices) {
                    if (v->getName() == infectedVertexName)
                        vertex = v;
                }

                vertex->setInfected(true);
                data.infectedVertices.push_back(vertex);
            }
        }

        // Load days
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            data.days = line.toInt();
        }
        else {
            data.loadSucces = false;
            return data;
        }

        // Load possible solutions
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList solutionStrings = line.split('|');
            for (const auto &solutionString : solutionStrings) {
                QStringList vertexNames = solutionString.split('&');

                QVector<Vertex*> solution = QVector<Vertex*>();
                for (const auto &vertexName : vertexNames) {
                    Vertex *vertex;
                    for (const auto v : data.vertices) {
                        if (v->getName() == vertexName)
                            vertex = v;
                    }

                    solution.push_back(vertex);
                }

                data.possibleSolutions.push_back(solution);
            }
        }

        file.close();

        data.loadSucces = true;
    }
    else {
        file.close();
        data.loadSucces = false;
    }

    return data;
}
