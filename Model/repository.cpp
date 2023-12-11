#include "repository.h"

#include <QFile>

Repository::Repository()
{

}

Repository::Data Repository::LoadFile(const QString &filePath)
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

void Repository::saveFile(const QString &filePath, const Data &data)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (file.isOpen()) {
        // Save vertices
        QStringList vertexNames;
        for (const auto &vertex : data.vertices) {
            vertexNames.append(vertex->getName());
        }
        file.write(vertexNames.join(',').append("\n").toUtf8());

        // Save connections
        QStringList connectionStrings;
        for (const auto &connection : data.connections) {
            connectionStrings.append(connection.first->getName() + "->" + connection.second->getName());
        }
        file.write(connectionStrings.join(',').append("\n").toUtf8());

        // Save infected vertices
        QStringList infectedVertexNames;
        for (const auto &infectedVertex : data.infectedVertices) {
            infectedVertexNames.append(infectedVertex->getName());
        }
        file.write(infectedVertexNames.join(',').append("\n").toUtf8());

        // Save days
        file.write(QString::number(data.days).append("\n").toUtf8());

        // Save possible solutions
        QStringList solutionStrings;
        for (const auto &solution : data.possibleSolutions) {
            QStringList vertexNames;
            for (const auto &vertex : solution) {
                vertexNames.append(vertex->getName());
            }
            solutionStrings.append(vertexNames.join('&'));
        }
        file.write(solutionStrings.join('|').append("\n").toUtf8());

        file.write("------------ // END OF FILE\n");
        file.close();
    }
    else {
        file.close();
    }
}
