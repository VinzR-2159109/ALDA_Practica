// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

// Source: https://doc.qt.io/qt-6/qtwidgets-graphicsview-elasticnodes-example.html

#ifndef EDGEVIEW_H
#define EDGEVIEW_H

#include <QGraphicsItem>

class VertexView;

class EdgeView : public QGraphicsItem
{
public:
    enum class ArrowType { SINGLE_TO_DEST, SINGLE_TO_SOURCE, TWOSIDED };

    EdgeView(VertexView *sourceNode, VertexView *destNode, ArrowType arrowType = EdgeView::ArrowType::SINGLE_TO_DEST);

    VertexView *sourceNode() const;
    VertexView *destNode() const;

    void setArrowType(ArrowType arrowType);
    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    VertexView *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;

    ArrowType m_arrowType;
};

#endif // EDGEVIEW_H
