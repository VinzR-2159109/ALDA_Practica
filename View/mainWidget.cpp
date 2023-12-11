#include "mainWidget.h"

#include <QBrush>
#include <QFileDialog>
#include <QHBoxLayout>

mainWidget::mainWidget(GraphWidget *graphWidget, QWidget *parent) : QWidget(parent), m_grapWidget{graphWidget}
{
    initUi();
    initConnections();

    m_data = GraphData();
}

mainWidget::~mainWidget()
{
    for (auto vertex : m_data.getVertices()) {
        delete vertex;
    }
}

void mainWidget::initUi()
{
    // create UI elements
    m_loadDataBtn = new QPushButton("Load");
    m_saveDataBtn = new QPushButton("Save");
    m_refreshDataBtn = new QPushButton("Refresh");

    m_dataListView = new DataListView(m_data);

    m_dayLabel = new QLabel();
    m_dayLabel->setStyleSheet("background-color:white; border: 1px solid gray;");

    // Create Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *bottomButtonLayout = new QHBoxLayout(this);

    // add buttons to bottem layout
    bottomButtonLayout->addWidget(m_loadDataBtn);
    bottomButtonLayout->addWidget(m_saveDataBtn);
    bottomButtonLayout->addWidget(m_refreshDataBtn);

    // Add to main layout
    mainLayout->addWidget(m_dataListView);
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
    QString filePath = QFileDialog::getOpenFileName(this, "Load Data", dirPath, "Text files (*.txt)");

    for (const auto &vertex : m_data.getVertices()) {
        delete vertex;
    }

    if (filePath.isEmpty())
        return;

    auto repoData = Repository().LoadFile(filePath);

    if (repoData.loadSucces == false)
        return;

    m_data = repoData.graphData;

    onRefreshData();
    updateUI();
}

void mainWidget::onSaveData()
{
    QString dirPath = QDir::currentPath().append("/Data");
    QString filePath = QFileDialog::getSaveFileName(this, "Save Data", dirPath, "Text files (*.txt)");

    if (filePath.isEmpty())
        return;

    Repository().saveFile(filePath, m_data);
}

void mainWidget::onRefreshData()
{
    m_grapWidget->setData(m_data);
}

void mainWidget::updateUI()
{
    // Fill UI
    m_dataListView->setData(m_data);
    m_dayLabel->setText(QString("Days: %1").arg(QString::number(m_data.getDays())));
}









