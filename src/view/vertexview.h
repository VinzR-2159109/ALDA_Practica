// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#ifndef VERTEXVIEW_H
#define VERTEXVIEW_H

#include "graphwidget.h"

#include <QGraphicsItem>
#include <QList>

class EdgeView;
class GraphWidget;

class VertexView : public QGraphicsItem
{
public:
    const static int VERTEX_SIZE = 40;
    const static int VERTEX_NAME_SIZE = 15;

    VertexView(Vertex *vertex, GraphWidget *graphWidget);

    void addEdge(EdgeView *edge);
    QList<EdgeView*> getEdges();

    enum { Type = UserType + 1 };
    int type() const override { return Type; }

    void calculateForces();
    bool advancePosition();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    Vertex *m_vertex;
    QColor m_color;
    QString m_name;

    QList<EdgeView *> m_edgeList;
    QPointF m_newPos;
    GraphWidget *m_graph;
};

#endif // VERTEXVIEW_H
