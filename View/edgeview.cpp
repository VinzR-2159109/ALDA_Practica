// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#include "edgeview.h"
#include "vertexview.h"

#include <QPainter>
#include <QtMath>

EdgeView::EdgeView(VertexView *sourceNode, VertexView *destNode, ArrowType arrowType)
    : source(sourceNode)
    , dest(destNode)
    , m_arrowType(arrowType)
{
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    adjust();
}

VertexView *EdgeView::sourceNode() const
{
    return source;
}

VertexView *EdgeView::destNode() const
{
    return dest;
}

void EdgeView::setArrowType(ArrowType arrowType)
{
    m_arrowType = arrowType;
}

void EdgeView::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
    qreal length = line.length();

    prepareGeometryChange();

    int vertexSize = VertexView::VERTEX_SIZE;

    if (length > qreal(vertexSize)) {
        QPointF edgeOffset((line.dx() * vertexSize / 2) / length, (line.dy() * vertexSize / 2) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF EdgeView::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void EdgeView::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());
    painter->setBrush(Qt::black);

    if (m_arrowType == ArrowType::SINGLE_TO_SOURCE || m_arrowType == ArrowType::TWOSIDED) {
        QPointF sourceArrowP1 = sourcePoint + QPointF(sin(angle + M_PI / 3) * arrowSize,
                                                      cos(angle + M_PI / 3) * arrowSize);
        QPointF sourceArrowP2 = sourcePoint + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                                      cos(angle + M_PI - M_PI / 3) * arrowSize);

        painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    }

    if (m_arrowType == ArrowType::SINGLE_TO_DEST || m_arrowType == ArrowType::TWOSIDED) {
        QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                                  cos(angle - M_PI / 3) * arrowSize);
        QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                                  cos(angle - M_PI + M_PI / 3) * arrowSize);

        painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
    }
}
