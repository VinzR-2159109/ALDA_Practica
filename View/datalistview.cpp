#include "datalistview.h"

#include <QInputDialog>
#include <QVBoxLayout>

DataListView::DataListView(GraphData &data, QWidget *parent)
    : QWidget(parent)
    , m_dataType{DataType::Vertices}
    , m_graphData{data}
{
    m_addBtn = new QPushButton("Add");
    m_deleteBtn = new QPushButton("Delete");

    m_showVertices = new QRadioButton("Vertices");
    m_showConnections = new QRadioButton("Connections");
    m_showInfectedVertices = new QRadioButton("Infected Vertices");
    m_showSolutions = new QRadioButton("Solutions");

    m_showVertices->setChecked(true);

    m_listView = new QListWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *editButtonsLayout = new QHBoxLayout();
    QHBoxLayout *radioButtonsLayout = new QHBoxLayout();

    mainLayout->addLayout(radioButtonsLayout);
    mainLayout->addWidget(m_listView);
    mainLayout->addLayout(editButtonsLayout);

    editButtonsLayout->addWidget(m_addBtn);
    editButtonsLayout->addWidget(m_deleteBtn);

    radioButtonsLayout->addWidget(m_showVertices);
    radioButtonsLayout->addWidget(m_showInfectedVertices);
    radioButtonsLayout->addWidget(m_showConnections);
    radioButtonsLayout->addWidget(m_showSolutions);

    connect(m_showVertices, &QRadioButton::clicked, this, [&]() { setDataType(DataType::Vertices); });
    connect(m_showConnections, &QRadioButton::clicked, this, [&]() { setDataType(DataType::Connections); });
    connect(m_showInfectedVertices, &QRadioButton::clicked, this, [&]() { setDataType(DataType::InfectedVertices); });
    connect(m_showSolutions, &QRadioButton::clicked, this, [&]() { setDataType(DataType::Solutions); });

    connect(m_addBtn, &QPushButton::clicked, this, &DataListView::onAdd);
    connect(m_deleteBtn, &QPushButton::clicked, this, &DataListView::onDelete);

    updateUI();
}

void DataListView::clear()
{
    m_listView->clear();
}

void DataListView::setData(GraphData &data)
{
    m_graphData = data;
    updateUI();
}

void DataListView::setDataType(DataType dataType)
{
    m_dataType = dataType;
    updateUI();
}

void DataListView::updateUI()
{
    m_listView->clear();

    QStringList itemStrings;

    switch (m_dataType) {
    case DataType::Vertices:
        for (const auto &vertex : m_graphData.getVertices()) {
            itemStrings.append(vertex->getName());
        }
        break;
    case DataType::InfectedVertices:
        for (const auto &infectedVertex : m_graphData.getInfectedVertices()) {
            itemStrings.append(infectedVertex->getName());
        }
        break;
    case DataType::Connections:
        for (const auto &connection : m_graphData.getConnections()) {
            itemStrings.append(connection.first->getName() + "->" + connection.second->getName());
        }
        break;
    case DataType::Solutions:
        for (const auto &solution : m_graphData.getSolutions()) {
            QStringList vertexNames;
            for (const auto &vertex : solution) {
                vertexNames.append(vertex->getName());
            }
            itemStrings.append(vertexNames.join(" or "));
        }
        break;
    }

    m_listView->addItems(itemStrings);
}

bool DataListView::onAdd()
{
    QString dialogText = "";
    switch (m_dataType) {
    case DataType::Vertices:
        dialogText = "Enter a vertex name (no spaces):";
        break;
    case DataType::InfectedVertices:
        dialogText = "Enter a vertex name (no spaces):";
        break;
    case DataType::Connections:
        dialogText = "Enter 2 vertex names (seperated by ','):";
        break;
    case DataType::Solutions:
        dialogText = "Enter multiple vertex name (seperated by ','):";
        break;
    }

    bool ok;
    QString text = QInputDialog::getText(
        this,
        "",
        dialogText,
        QLineEdit::Normal,
        "",
        &ok
    );

    if (!ok) return false;

    switch (m_dataType) {
    case DataType::Vertices:
        m_graphData.addVertex(new Vertex(text));
        break;
    case DataType::InfectedVertices:
        m_graphData.addInfectedVertexFromString(text);
        break;
    case DataType::Connections:
        m_graphData.addConnectionFromString(text);
        break;
    case DataType::Solutions:
        m_graphData.addSolutionFromString(text);
        break;
    }

    updateUI();

    return true;
}

void DataListView::onDelete()
{
    switch (m_dataType) {
    case DataType::Vertices:
        m_graphData.deleteVertexFromString(m_listView->selectedItems().first()->text());
        break;
    case DataType::InfectedVertices:
        m_graphData.deleteInfectedVertexFromString(m_listView->selectedItems().first()->text());
        break;
    case DataType::Connections:
        m_graphData.deleteConnectionFromString(m_listView->selectedItems().first()->text());
        break;
    case DataType::Solutions:
        m_graphData.deleteSolutionFromString(m_listView->selectedItems().first()->text());
        break;
    }

    updateUI();
}
