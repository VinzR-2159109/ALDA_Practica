#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "View/graphwidget.h"
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
    QListWidget *m_verticesList;
    QListWidget *m_connectionsList;
    QListWidget *m_infectedVerticesList;
    QListWidget *m_solutionsList;
    QLabel *m_dayLabel;

    void initUi();
    void initConnections();

    void loadData();
    void updateUI() const;
};

#endif // MAINWIDGET_H
