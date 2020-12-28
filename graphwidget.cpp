#include "graphwidget.h"
#include "graph.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    /* Support 1000 edges */
    graph = new Graph(1000);
    QGraphicsScene* scene = new QGraphicsScene(parent);
    par = parent;
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    parent->setContentsMargins(0, 0, 0, 0);
    /* scene->setSceneRect(view.sceneRect()); */
    /* scene->setSceneRect(0, 0, this->size().width(), this->size().height()); */
    /* qDebug() << this->size().width() << ' ' << this->size().height() <<'\n'; */
    /* qDebug() << this->rect().topLeft().rx() << ' ' << this->rect().topLeft().ry(); */
    
    qDebug() << parent->width() << ' '  << parent->height() << '\n';

    scene->setSceneRect(-200, -200, this->width(), this->height());
    setScene(scene);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setMinimumSize(1000, 600);
    QSizePolicy policy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    setSizePolicy(policy);
}

void GraphWidget::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
    /* qDebug() << view->width() << ' ' << view->height() << '\n'; */
    /* qDebug() << view->sceneRect().width() << ' ' << view->sceneRect().height() << '\n'; */
}

void GraphWidget::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void GraphWidget::resizeEvent(QResizeEvent* event) {
    //this->
    scene()->setSceneRect(-200, -200, this->width(), this->height());
    qDebug() << par->width() << par->height();
    update();

}

void GraphWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    QVector<Node *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (Node *node = qgraphicsitem_cast<Node *>(item))
            nodes << node;
    }
    for (Node *node : qAsConst(nodes))
        node->calculateForces();
    bool itemsMoved = false;
    for (Node *node : qAsConst(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., event->angleDelta().y() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::shuffle()
{
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (qgraphicsitem_cast<Node *>(item))
            item->setPos(-150 + QRandomGenerator::global()->bounded(300), -150 + QRandomGenerator::global()->bounded(300));
    }
}

void GraphWidget::zoomIn()
{
    scaleView(qreal(1.2));
}

void GraphWidget::zoomOut()
{
    scaleView(1 / qreal(1.2));
}

Node* GraphWidget::addNode(int num) {
    Node* node = nodeMap[num];
    if (node == NULL) {
        nodeMap[num] = new Node(this);
    } else return node;
    node = nodeMap[num];
    node->setLabel(QString::number(num));
    node->setPos(-150 + QRandomGenerator::global()->bounded(500), -150 + QRandomGenerator::global()->bounded(300));
    scene()->addItem(node);
    return node;
}


void GraphWidget::addEdge(int u, int v, int w) {
    if (u == w) return;
    graph->addEdge(u, v, w);
}

void GraphWidget::draw() {
    int n = graph->getN();
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            if (graph->checkEdge(i, j))
                scene()->addItem(new Edge(i, j, addNode(i), addNode(j), graph, graph->getWeight(i, j)));
        }
    }
}

void GraphWidget::clear() {
    scene()->clear();
    nodeMap.clear();
    graph->clear();

}
