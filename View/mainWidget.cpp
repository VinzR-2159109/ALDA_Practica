#include "mainWidget.h"

#include <QBrush>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMetaEnum>

#include <Model/strategycontext.h>
#include <Model/strategyfactory.h>

MainWidget::MainWidget(GraphWidget *graphWidget, QWidget *parent)
    : QWidget(parent)
    , m_grapWidget{graphWidget}
{
    initUi();
    initConnections();

    m_data = GraphData();
}

MainWidget::~MainWidget()
{
    for (auto vertex : m_data.getVertices()) {
        delete vertex;
    }
}

void MainWidget::initUi()
{
    // create UI elements
    m_loadDataBtn = new QPushButton("Load");
    m_saveDataBtn = new QPushButton("Save");
    m_refreshDataBtn = new QPushButton("Refresh");

    m_daySpinner = new QSpinBox();
    m_dataListView = new DataListView(m_data);
    QLabel *dayLabel = new QLabel("Days: ");
    dayLabel->setMaximumWidth(40);

    // Add all strategies
    m_runBtn = new QPushButton("Run");
    m_runBtn->setMaximumWidth(40);
    m_graphStrategyComboBox = new QComboBox();
    QMetaEnum metaEnum = QMetaEnum::fromType<StrategyFactory::AllStrategies>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        m_graphStrategyComboBox->addItem(metaEnum.key(i));
    }

    // Create Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *bottomButtonLayout = new QHBoxLayout();
    QHBoxLayout *dayLayout = new QHBoxLayout();
    QHBoxLayout *strategyLayout = new QHBoxLayout();

    // Add strategy and run button to strategy layout
    strategyLayout->addWidget(m_graphStrategyComboBox);
    strategyLayout->addWidget(m_runBtn);

    // Add daySpinner and dayLabel to dayLayout
    dayLayout->addWidget(dayLabel);
    dayLayout->addWidget(m_daySpinner);

    // Add buttons to bottem layout
    bottomButtonLayout->addWidget(m_loadDataBtn);
    bottomButtonLayout->addWidget(m_saveDataBtn);
    bottomButtonLayout->addWidget(m_refreshDataBtn);

    // Add to main layout
    mainLayout->addLayout(strategyLayout);
    mainLayout->addLayout(dayLayout);
    mainLayout->addWidget(m_dataListView);
    mainLayout->addLayout(bottomButtonLayout);
}

void MainWidget::initConnections()
{
    connect(m_loadDataBtn, &QPushButton::clicked, this, &MainWidget::onLoadData);
    connect(m_saveDataBtn, &QPushButton::clicked, this, &MainWidget::onSaveData);
    connect(m_refreshDataBtn, &QPushButton::clicked, this, &MainWidget::onRefreshData);

    connect(m_runBtn, &QPushButton::clicked, this, &MainWidget::onRunStrategy);

    connect(m_daySpinner, &QSpinBox::valueChanged, this, [&]() { m_data.setDays(m_daySpinner->value()); });    
}

void MainWidget::updateUI()
{
    // Fill UI
    m_dataListView->setData(m_data);
    m_daySpinner->setValue(m_data.getDays());
}

void MainWidget::onLoadData()
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

void MainWidget::onSaveData()
{
    QString dirPath = QDir::currentPath().append("/Data");
    QString filePath = QFileDialog::getSaveFileName(this, "Save Data", dirPath, "Text files (*.txt)");

    if (filePath.isEmpty())
        return;

    Repository().saveFile(filePath, m_data);
}

void MainWidget::onRefreshData()
{
    m_grapWidget->setData(m_data);
}

void MainWidget::onRunStrategy()
{
    BaseStrategy *strategy = StrategyFactory().getStrategy(StrategyFactory::AllStrategies::Strategy1);

    strategy->setData(m_data);

    m_strategyContext.setStrategy(strategy);
    auto result = m_strategyContext.runStrategy();

    QStringList sourceNames;
    for (const auto &vertex : result) {
        sourceNames.push_back(vertex->getName());
    }

    QMessageBox::information(this, "Result", QString("The source(s) are: %1").arg(sourceNames.join(',')));
}









