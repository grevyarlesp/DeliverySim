#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <queue>

using namespace std;

class Graph
{
private:
    QVector<QVector<QPair<int, QPair<int, int> > > > g; // Graph reprenstation as an adjencency list
    QVector<QVector< int> > mg;
    QVector<QVector< int> > allow;
    int n, mx;
public:
    Graph(int max_size);
    void clear();
    void addEdge(int u, int v, int c, int allow);
    bool checkEdge(int u, int v);
    int getN();
    int getWeight(int u, int v);
    int getAllow(int u, int v);
    const QVector<QVector<QPair<int, QPair<int, int> > > >* adjencencyList() const;
    
};

#endif // GRAPH_H
