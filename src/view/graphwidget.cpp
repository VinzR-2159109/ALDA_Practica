// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#include "graphwidget.h"
#include "edgeview.h"
#include "vertexview.h"

#include <math.h>

#include <QKeyEvent>
#include <QRandomGenerator>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent) 
{
    m_scene = new QGraphicsScene(this);
    m_scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    m_scene->setSceneRect(rect());
    setScene(m_scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    scale(qreal(0.8), qreal(0.8));

    setTransformationAnchor(QGraphicsView::NoAnchor);
    setResizeAnchor(QGraphicsView::NoAnchor);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void GraphWidget::clearScreen()
{
    for (const auto vertexView : m_vertexViews) {
        delete vertexView;
    }
    m_vertexViews.clear();

    for (const auto edge : m_edges) {
        delete edge;
    }
    m_edges.clear();
}

void GraphWidget::setData(GraphData *data)
{
    clearScreen();

    if (!data)
        return;

    for (const auto vertex : data->getVertices()) {
        VertexView *vertexView = new VertexView(vertex, this);
        m_scene->addItem(vertexView);

        m_vertexViews.insert(vertex, vertexView);
    }

    for (const auto &connectionKey : data->getConnections().keys()) {
        for (const auto &connectionValue : data->getConnections().values(connectionKey)) {
            VertexView *vertexView1 = m_vertexViews.value(connectionKey);
            VertexView *vertexView2 = m_vertexViews.value(connectionValue);

            bool hasEdge = false;
            for (const auto edge : vertexView2->getEdges()) {
                if (edge->destNode() == vertexView1) {
                    edge->setArrowType(EdgeView::ArrowType::TWOSIDED);
                    hasEdge = true;
                    break;
                }
            }

            if (!hasEdge) {
                EdgeView *edge = new EdgeView(vertexView1, vertexView2);
                m_edges.push_back(edge);
                m_scene->addItem(edge);
            }
        }
    }

    for (const auto vertexView : m_vertexViews) {
       vertexView->setPos(QRandomGenerator::global()->bounded(rect().bottomRight().x()), QRandomGenerator::global()->bounded(rect().bottomRight().y()));
    }
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1);
}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QList<VertexView *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (VertexView *node = qgraphicsitem_cast<VertexView *>(item))
            nodes << node;
    }

    for (VertexView *node : std::as_const(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (VertexView *node : std::as_const(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::resizeEvent(QResizeEvent *event)
{
    m_scene->setSceneRect(rect());
    itemMoved();
}
