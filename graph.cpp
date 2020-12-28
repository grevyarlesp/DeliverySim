#include "graph.h"
#include <QPair>

using namespace std;

Graph::Graph(int max_size)
{
    n = max_size;
    g = QVector<QVector< QPair<int, int>> >(n + 1);
    mg = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
}

void Graph::clear() {
    mg.clear();
    g.clear();
    g = QVector<QVector< QPair<int, int>> >(n + 1);
    mg = QVector<QVector<int> >(n + 1, QVector<int>(n + 1, 0));
}

void Graph::addEdge(int u, int v, int c) {
    g[u].push_back(qMakePair(v, c));
    if (mg[u][v]) {
        mg[u][v] = min(mg[u][v], c);
    } else 
        mg[u][v] = c;
}

bool Graph::checkEdge(int u, int v) {
    return mg[u][v] > 0;
}

int Graph::getN() {
    return n;
}

int Graph::getWeight(int u, int v) {
    return mg[u][v];
}

