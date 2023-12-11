// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#include "edgeview.h"
#include "vertexview.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>

VertexView::VertexView(Vertex *vertex, GraphWidget *graphWidget)
    : m_vertex{vertex}
    , m_color{m_vertex->getIsInfected() ? Qt::yellow : Qt::green}
    , m_name{vertex->getName()}
    , m_graph(graphWidget)
{   
    setFlag(ItemSendsGeometryChanges);
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
}

void VertexView::addEdge(EdgeView *edge)
{
    m_edgeList.append(edge);
    edge->adjust();
}

QList<EdgeView *> VertexView::getEdges()
{
    return m_edgeList;
}

void VertexView::calculateForces()
{
    // Sum up all forces pushing this item away
    qreal xvel = 0;
    qreal yvel = 0;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        VertexView *node = qgraphicsitem_cast<VertexView *>(item);
        if (!node)
            continue;

        QPointF vec = mapToItem(node, 0, 0);
        qreal dx = vec.x();
        qreal dy = vec.y();
        double l = .5 * (dx * dx + dy * dy);
        if (l > 0) {
            xvel += (dx * 150.0) / l;
            yvel += (dy * 150.0) / l;
        }
    }

    // Now subtract all forces pulling items together
    double weight = (m_edgeList.size() + 1) * 8;
    for (const EdgeView *edge : std::as_const(m_edgeList)) {
        QPointF vec;
        if (edge->sourceNode() == this)
            vec = mapToItem(edge->destNode(), 0, 0);
        else
            vec = mapToItem(edge->sourceNode(), 0, 0);
        xvel -= vec.x() / weight;
        yvel -= vec.y() / weight;
    }

    if (qAbs(xvel) < 0.1 && qAbs(yvel) < 0.1)
        xvel = yvel = 0;

    QRectF sceneRect = scene()->sceneRect();
    m_newPos = pos() + QPointF(xvel, yvel);
    m_newPos.setX(qMin(qMax(m_newPos.x(), sceneRect.left()), sceneRect.right()));
    m_newPos.setY(qMin(qMax(m_newPos.y(), sceneRect.top()), sceneRect.bottom()));
}

bool VertexView::advancePosition()
{
    if (m_newPos == pos())
        return false;

    setPos(m_newPos);
    return true;
}

QRectF VertexView::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -VERTEX_SIZE / 2 - adjust, -VERTEX_SIZE / 2 - adjust, VERTEX_SIZE + adjust, VERTEX_SIZE + adjust);
}

QPainterPath VertexView::shape() const
{
    QPainterPath path;
    path.addEllipse(-VERTEX_SIZE / 2, -VERTEX_SIZE / 2, VERTEX_SIZE, VERTEX_SIZE);
    return path;
}

void VertexView::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
    // Fill
    painter->setBrush(m_color);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-VERTEX_SIZE / 2, -VERTEX_SIZE / 2, VERTEX_SIZE, VERTEX_SIZE);

    // Text
    QRectF ellipseRect = QRectF(-VERTEX_SIZE / 2, -VERTEX_SIZE / 2, VERTEX_SIZE, VERTEX_SIZE);

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(VERTEX_NAME_SIZE);
    painter->setFont(font);

    painter->setPen(Qt::black);
    painter->drawText(ellipseRect, Qt::AlignCenter, m_name);
}

QVariant VertexView::itemChange(GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
    case ItemPositionHasChanged:
        for (EdgeView *edge : std::as_const(m_edgeList))
            edge->adjust();
        m_graph->itemMoved();
        break;
    default:
        break;
    };

    return QGraphicsItem::itemChange(change, value);
}
