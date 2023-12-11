#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "View/graphwidget.h"
#include "View/datalistview.h"
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <Model/repository.h>

class mainWidget : public QWidget
{
public:
    mainWidget(GraphWidget *graphWidget, QWidget *parent = nullptr);
    ~mainWidget();

private:
    GraphWidget *m_grapWidget;
    GraphData m_data;

    // -- UI --
    QPushButton *m_loadDataBtn;
    QPushButton *m_refreshDataBtn;
    QPushButton *m_saveDataBtn;

    DataListView *m_dataListView;

    QLabel *m_dayLabel;

    void initUi();
    void initConnections();

    void onLoadData();
    void onSaveData();
    void onRefreshData();

    void updateUI();
};

#endif // MAINWIDGET_H
