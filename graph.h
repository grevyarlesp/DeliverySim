#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <queue>

using namespace std;

class Graph
{
private:
    QVector<QVector<QPair<int,int> > > g; // Graph reprenstation as an adjencency list
    QVector<QVector< int> > mg;
    int n;
public:
    Graph(int max_size);
    void clear();
    void addEdge(int u, int v, int c);
    bool checkEdge(int u, int v);
    int getN();
    int getWeight(int u, int v);
};

#endif // GRAPH_H
