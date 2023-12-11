#include "mainWidget.h"

#include <QBrush>
#include <QFileDialog>
#include <QHBoxLayout>

mainWidget::mainWidget(GraphWidget *graphWidget, QWidget *parent) : QWidget(parent), m_grapWidget{graphWidget}
{
    initUi();
    initConnections();
}

mainWidget::~mainWidget()
{
    for (auto vertex : m_data.vertices) {
        delete vertex;
    }
}

void mainWidget::initUi()
{
    // create UI elements
    m_loadDataBtn = new QPushButton("Load");
    m_saveDataBtn = new QPushButton("Save");
    m_refreshDataBtn = new QPushButton("Refresh");
    m_verticesList = new QListWidget();
    m_connectionsList = new QListWidget();
    m_infectedVerticesList = new QListWidget();
    m_solutionsList = new QListWidget();
    m_dayLabel = new QLabel();
    m_dayLabel->setStyleSheet("background-color:white; border: 1px solid gray;");

    QLabel *verticesListLabel = new QLabel("Vertices");
    verticesListLabel->setAlignment(Qt::AlignCenter);
    QLabel *connectionsListLabel = new QLabel("Connections");
    connectionsListLabel->setAlignment(Qt::AlignCenter);
    QLabel *infectedVerticesListLabel = new QLabel("Infected Vertices");
    infectedVerticesListLabel->setAlignment(Qt::AlignCenter);
    QLabel *solutionsListLabel = new QLabel("Solutions");
    solutionsListLabel->setAlignment(Qt::AlignCenter);

    // Create Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *bottomButtonLayout = new QHBoxLayout(this);

    // add buttons to bottem layout
    bottomButtonLayout->addWidget(m_loadDataBtn);
    bottomButtonLayout->addWidget(m_saveDataBtn);
    bottomButtonLayout->addWidget(m_refreshDataBtn);

    // Add to main layout
    mainLayout->addWidget(verticesListLabel);
    mainLayout->addWidget(m_verticesList);
    mainLayout->addWidget(connectionsListLabel);
    mainLayout->addWidget(m_connectionsList);
    mainLayout->addWidget(infectedVerticesListLabel);
    mainLayout->addWidget(m_infectedVerticesList);
    mainLayout->addWidget(solutionsListLabel);
    mainLayout->addWidget(m_solutionsList);
    mainLayout->addWidget(m_dayLabel);
    mainLayout->addLayout(bottomButtonLayout);
}

void mainWidget::initConnections()
{
    connect(m_loadDataBtn, &QPushButton::clicked, this, &mainWidget::onLoadData);
    connect(m_saveDataBtn, &QPushButton::clicked, this, &mainWidget::onSaveData);
    connect(m_refreshDataBtn, &QPushButton::clicked, this, &mainWidget::onRefreshData);
}

void mainWidget::onLoadData()
{
    QString dirPath = QDir::currentPath().append("/Data");
    QString filePath = QFileDialog::getOpenFileName(this, "Open Data", dirPath, "Text files (*.txt)");

    for (const auto &vertex : m_data.vertices) {
        delete vertex;
    }

    if (filePath.isEmpty())
        return;

    m_data = Repository().LoadFile(filePath);
    onRefreshData();

    updateUI();
}

void mainWidget::onSaveData()
{

}

void mainWidget::onRefreshData()
{
    m_grapWidget->setData(m_data);
}

void mainWidget::updateUI() const
{
    // Clear UI
    m_verticesList->clear();
    m_connectionsList->clear();
    m_infectedVerticesList->clear();
    m_solutionsList->clear();

    if (m_data.loadSucces == false)
        return;

    // Fill UI
    for (const auto &vertex : m_data.vertices) {
        m_verticesList->addItem(vertex->getName());
    }

    for (const auto &connection : m_data.connections) {
        m_connectionsList->addItem(QString("%1 -> %2").arg(connection.first->getName()).arg(connection.second->getName()));
    }

    for (const auto &vertex : m_data.infectedVertices) {
        m_infectedVerticesList->addItem(vertex->getName());
    }

    for (const auto &solution : m_data.possibleSolutions) {
        QString solutionString = "";
        for (const auto &solutionVertex : solution) {
            solutionString.append(QString(",%1").arg(solutionVertex->getName()));
        }
        solutionString.removeAt(0);
        m_solutionsList->addItem(solutionString);
    }

    m_dayLabel->setText(QString("Days: %1").arg(QString::number(m_data.days)));
}









