#ifndef DATALISTVIEW_H
#define DATALISTVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>

#include <Model/repository.h>
#include <Model/vertex.h>

class DataListView : public QWidget
{
public:
    enum class DataType {
        Vertices, Connections, InfectedVertices, Solutions
    };

    DataListView(GraphData &data, QWidget *parent = nullptr);

    void clear();
    void setData(GraphData &data);
    void setDataType(DataType dataType);

private:
    DataType m_dataType;

    QPushButton *m_addBtn;
    QPushButton *m_editBtn;
    QPushButton *m_deleteBtn;

    QRadioButton *m_showVertices;
    QRadioButton *m_showConnections;
    QRadioButton *m_showInfectedVertices;
    QRadioButton *m_showSolutions;

    QListWidget *m_listView;

    GraphData &m_graphData;

    void updateUI();

private slots:
    void onAdd();
    void onEdit();
    void onDelete();
};

#endif // DATALISTVIEW_H
