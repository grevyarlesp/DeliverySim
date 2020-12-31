#include "shortestpath.h"

ShortestPath::ShortestPath(Graph* graph, GraphWidget* graphWidget) {
    this->graph = graph;
    d = QVector<int>(graph->getN() + 1, 1e9 + 7);
    this->graphWidget = graphWidget;
    g = graph->adjencencyList();
}

int ShortestPath::execute(int s, int t, int vehicle, bool recolor) {
    g = graph->adjencencyList();
    d = QVector<int>(graph->getN() + 1, 1e9 + 7);
    trace = QVector<int>(graph->getN() + 1, -1);
    q.push(make_pair(0, s));
    d[s] = 0;
    while (! q.empty()) {
        int u = q.top().second; int dist = q.top().first;
        q.pop();
        if (dist != d[u]) continue;
        for (int i  = 0; i < (*g)[u].size(); ++i) {
            int v = (*g)[u][i].first,  c = (*g)[u][i].second.first, allow = (*g)[u][i].second.second;
            if ((allow == 3 || vehicle == allow) && dist + c < d[v]) {
                d[v] = dist + c;
                trace[v] = u;
                q.push(make_pair(d[v], v));
            }
        }
    }
    qDebug() << "Found" << trace[t];
    if (trace[t] != -1 && recolor)
        path(t, -1);
    return d[t];
}

void ShortestPath::path(int s, int last) {
    if (s == -1) return;
    if (last != -1) {
        graphWidget->getEdge(s, last)->setColor(Qt::red);
    }
    path(trace[s], s);
    qDebug() << s;
}
