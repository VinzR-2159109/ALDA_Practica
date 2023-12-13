// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "edgeview.h"
#include "graphdata.h"

#include <QGraphicsView>

class VertexView;

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);

    void clearScreen();
    void setData(GraphData *data);
    void itemMoved();

protected:
    void timerEvent(QTimerEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QGraphicsScene *m_scene;
    QHash<Vertex*, VertexView*> m_vertexViews;
    QVector<EdgeView*> m_edges;

    int timerId = 0;
    VertexView *centerNode;
};

#endif // GRAPHWIDGET_H
