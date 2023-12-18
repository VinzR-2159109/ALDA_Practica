#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "strategycontext.h"
#include "graphwidget.h"
#include "datalistview.h"

#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>

class MainWidget : public QWidget
{
public:
    MainWidget(GraphWidget *graphWidget, QWidget *parent = nullptr);

private:
    GraphWidget *m_grapWidget;
    GraphData *m_data;

    StrategyContext m_strategyContext;

    // -- UI --
    QPushButton *m_loadDataBtn;
    QPushButton *m_refreshDataBtn;
    QPushButton *m_saveDataBtn;

    DataListView *m_dataListView;
    QSpinBox *m_daySpinner;

    QComboBox *m_graphStrategyComboBox;
    QPushButton *m_runBtn;

    void initUi();
    void initConnections();

    void updateUI();

    void onLoadData();
    void onSaveData();
    void onRefreshData();

    void onRunStrategy();
};

#endif // MAINWIDGET_H