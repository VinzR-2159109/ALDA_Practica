#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "View/graphwidget.h"
#include "View/listvieweditview.h"
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <Model/repository.h>

class mainWidget : public QWidget
{

    Q_OBJECT

public:
    mainWidget(GraphWidget *graphWidget, QWidget *parent = nullptr);
    ~mainWidget();

private:
    GraphWidget *m_grapWidget;
    Repository::Data m_data;

    // -- UI --
    QPushButton *m_loadDataBtn;
    QPushButton *m_refreshDataBtn;
    QPushButton *m_saveDataBtn;

    ListViewEditView<Vertex*> *m_verticesList;
    ListViewEditView<std::pair<Vertex*, Vertex*>> *m_connectionsList;
    ListViewEditView<Vertex*> *m_infectedVerticesList;
    ListViewEditView<QVector<Vertex*>> *m_solutionsList;

    QLabel *m_dayLabel;

    void initUi();
    void initConnections();

    void onLoadData();
    void onSaveData();
    void onRefreshData();

    void updateUI();
};

#endif // MAINWIDGET_H
