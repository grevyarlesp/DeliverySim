/* Copyright (C) 2018 The Qt Company Ltd. */

/* Redistribution and use in source and binary forms, with or without */
/* modification, are permitted provided that the following conditions are */
/* met: */
/*  * Redistributions of source code must retain the above copyright */
/*    notice, this list of conditions and the following disclaimer. */
/*  * Redistributions in binary form must reproduce the above copyright */
/*    notice, this list of conditions and the following disclaimer in */
/*    the documentation and/or other materials provided with the */
/*    distribution. */
/*  * Neither the name of The Qt Company Ltd nor the names of its */
/*    contributors may be used to endorse or promote products derived */
/*    from this software without specific prior written permission. */

/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT */
/* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QDebug> 
#include "node.h"
#include "edge.h"
#include <QRandomGenerator>
#include <QWheelEvent>
#include "graph.h"


/* Circular Dependecy; Foward declaration */
class Node;

/* Specify that this class use its own signals and slots */
class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void itemMoved();
    Node* addNode(int num);
    Graph* graph;
    void addEdge(int u, int v, int w);
    void draw();
    void clear();
public slots: 
    void shuffle();
    void zoomIn();
    void zoomOut();
protected:
    void resizeEvent(QResizeEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void scaleView(qreal scaleFactor);
private:
    
    int timerId = 0;
    QMap<int, Node*> nodeMap;
    Node *centerNode;
    QWidget* par;
    /* QGraphicsScene* scene; */
};


#endif // GRAPHWIDGET_H
