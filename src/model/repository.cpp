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
    data.graphData = new GraphData();

    if (file.isOpen()) {
        QString line = "";

        // Load all vertices
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList vertexNames = line.split(',');
            for (const auto &name : vertexNames) {
                data.graphData->addVertex(new Vertex(name));
            }
        }

        // Load connections
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList connectionStrings = line.split(',');
            for (auto &connectionString : connectionStrings) {
                QString vertexNames = connectionString.replace("->", ",");
                data.graphData->addConnectionFromString(vertexNames);
            }
        }

        // Load infected vertices
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList infectedVertexNames = line.split(',');
            for (auto &infectedVertexName : infectedVertexNames) {
                data.graphData->addInfectedVertexFromString(infectedVertexName);
            }
        }

        // Load days
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            data.graphData->setDays(line.toInt());
        }
        else {
            data.loadSucces = false;
            return data;
        }

        // Load possible solutions
        line = file.readLine().replace('\n', "");
        if (!line.isEmpty()) {
            QStringList solutionStrings = line.split('|');
            for (auto &solutionString : solutionStrings) {
                QString vertexNames = solutionString.replace('&', ',');
                data.graphData->addSolutionFromString(vertexNames);
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

void Repository::saveFile(const QString &filePath, const GraphData *data)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    if (file.isOpen()) {
        // Save vertices
        QStringList vertexNames;
        for (const auto &vertex : data->getVertices()) {
            vertexNames.append(vertex->getName());
        }
        file.write(vertexNames.join(',').append("\n").toUtf8());

        // Save connections
        QStringList connectionStrings;
        for (const auto &connectionKey : data->getConnections().keys()) {
            for (const auto &connectionValue : data->getConnections().values(connectionKey)) {
                connectionStrings.append(connectionKey->getName() + "->" + connectionValue->getName());
            }
        }
        file.write(connectionStrings.join(',').append("\n").toUtf8());

        // Save infected vertices
        QStringList infectedVertexNames;
        for (const auto &infectedVertex : data->getInfectedVertices()) {
            infectedVertexNames.append(infectedVertex->getName());
        }
        file.write(infectedVertexNames.join(',').append("\n").toUtf8());

        // Save days
        file.write(QString::number(data->getDays()).append("\n").toUtf8());

        // Save possible solutions
        QStringList solutionStrings;
        for (const auto &solution : data->getSolutions()) {
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
