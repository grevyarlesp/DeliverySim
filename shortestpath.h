#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H


#include "graph.h"
#include "graphwidget.h"
#include <queue>
#include <QPainter>
#include <QPair>

using namespace std;

class ShortestPath
{
private:
    QVector<QVector<QPair<int, QPair<int ,int> > > > *g; // Graph reprenstation as an adjencency list
    Graph* graph;
    QVector<int> d, trace;
    priority_queue< pair<int, int> > q;
    GraphWidget* graphWidget;
    void path(int s, int last);
public:
    ShortestPath(Graph* graph, GraphWidget* graphWidget);
    int execute(int s, int t, int vehicle, bool recolor=false);
};

#endif // SHORTESTPATH_H
