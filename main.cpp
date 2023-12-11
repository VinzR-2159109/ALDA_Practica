// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include "View/graphwidget.h"
#include "View/mainWidget.h"

#include <QApplication>
#include <QTime>
#include <QMainWindow>
#include <QHBoxLayout>
#include <QSplitter>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window = QWidget();
    window.resize(1000, 500);

    QHBoxLayout *hLayout = new QHBoxLayout(&window);

    GraphWidget *graphWidget = new GraphWidget;
    QSizePolicy graphWidgetSize(QSizePolicy::Preferred, QSizePolicy::Preferred);
    graphWidgetSize.setHorizontalStretch(2);
    graphWidget->setSizePolicy(graphWidgetSize);
    
    MainWidget *informationWidget = new MainWidget(graphWidget);
    QSizePolicy informationWidgetSize(QSizePolicy::Preferred, QSizePolicy::Preferred);
    informationWidgetSize.setHorizontalStretch(1);
    informationWidget->setSizePolicy(informationWidgetSize);

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(informationWidget);
    splitter->addWidget(graphWidget);

    QFrame *splitterLine = new QFrame();
    splitterLine->setFrameShape(QFrame::VLine);
    splitterLine->setFrameShadow(QFrame::Sunken);

    hLayout->addWidget(splitter);

    window.show();
    return app.exec();
}
