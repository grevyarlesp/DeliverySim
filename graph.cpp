#include "graph.h"
#include <QPair>

using namespace std;

Graph::Graph(int max_size)
{
    mx = 0;
    n = max_size;
    g = QVector<QVector< QPair<int, QPair<int, int>>> >(n + 1);
    mg = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
    
    allow = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
}

void Graph::clear() {
    mg.clear();
    g.clear();

    mx = 0;
    g = QVector<QVector< QPair<int, QPair<int, int>>> >(n + 1);
    mg = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
    allow = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
}

void Graph::addEdge(int u, int v, int c, int allow) {
    mx = max(mx, u);
    mx = max(mx, v);
    g[u].push_back(qMakePair(v, qMakePair(c, allow)));
    if (mg[u][v]) {
        mg[u][v] = min(mg[u][v], c);
    } else 
        mg[u][v] = c;
    this->allow[u][v] = allow;
}

bool Graph::checkEdge(int u, int v) {
    return mg[u][v] > 0;
}

int Graph::getAllow(int u, int v) {
    return allow[u][v];
}

int Graph::getN() {
    return mx;
}

int Graph::getWeight(int u, int v) {
    return mg[u][v];
}


QVector<QVector<QPair<int, QPair<int, int>> > >* Graph::adjencencyList() { 
    return &g;
}
