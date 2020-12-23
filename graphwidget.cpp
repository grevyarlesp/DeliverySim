#include "graphwidget.h"



GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
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
    /* setWindowTitle(tr("Elastic Nodes")); */
    /* Node *node1 = new Node(this); */
    /* Node *node2 = new Node(this); */
    /* Node *node3 = new Node(this); */
    /* Node *node4 = new Node(this); */
    /* centerNode = new Node(this); */
    /* Node *node6 = new Node(this); */
    /* Node *node7 = new Node(this); */
    /* Node *node8 = new Node(this); */
    /* Node *node9 = new Node(this); */
    /* Node *node10 = new Node(this); */
    /* scene->addItem(node1); */
    /* scene->addItem(node2); */
    /* scene->addItem(node3); */
    /* scene->addItem(node4); */
    /* scene->addItem(centerNode); */
    /* scene->addItem(node6); */
    /* scene->addItem(node7); */
    /* scene->addItem(node8); */
    /* scene->addItem(node9); */
    /* scene->addItem(node10); */
    /* scene->addItem(new Edge(node1, node2)); */
    /* scene->addItem(new Edge(node2, node3)); */
    /* scene->addItem(new Edge(node2, centerNode)); */
    /* scene->addItem(new Edge(node3, node6)); */
    /* scene->addItem(new Edge(node4, node1)); */
    /* scene->addItem(new Edge(node4, centerNode)); */
    /* scene->addItem(new Edge(centerNode, node6)); */
    /* scene->addItem(new Edge(centerNode, node8)); */
    /* scene->addItem(new Edge(node6, node9)); */
    /* scene->addItem(new Edge(node7, node4)); */
    /* scene->addItem(new Edge(node8, node7)); */
    /* scene->addItem(new Edge(node9, node8)); */
    /* scene->addItem(new Edge(node9, node10)); */

    /* node1->setPos(-50, -50); */
    /* node2->setPos(0, -50); */
    /* node3->setPos(50, -50); */
    /* node4->setPos(-50, 0); */
    /* centerNode->setPos(0, 0); */
    /* node6->setPos(50, 0); */
    /* node7->setPos(-50, 50); */
    /* node8->setPos(0, 50); */
    /* node9->setPos(50, 50); */
    /* node10->setPos(60, 60); */
    /* view.fitInView(scene, Qt::IgnoreAspectRatio); */
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

    // Text
    /* QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4, */
    /*                 sceneRect.width() - 4, sceneRect.height() - 4); */
    /* QString message(tr("Click and drag the nodes around, and zoom with the mouse " */
    /*                    "wheel or the '+' and '-' keys")); */

    /* QFont font = painter->font(); */
    /* font.setBold(true); */
    /* font.setPointSize(14); */
    /* painter->setFont(font); */
    /* painter->setPen(Qt::lightGray); */
    /* painter->drawText(textRect.translated(2, 2), message); */
    /* painter->setPen(Qt::black); */
    /* painter->drawText(textRect, message); */
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
    scene()->addItem(new Edge(addNode(u), addNode(v), w));

}

void GraphWidget::clear() {
    scene()->clear();
    nodeMap.clear();

}
