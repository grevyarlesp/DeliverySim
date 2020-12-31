#include "edge.h"

qreal Edge::height = 20.0;
qreal Edge::Pi = acos(-1.0);

Edge::Edge(int iSource, int iDest, Node *sourceNode, Node *destNode, Graph* graph, int w) : source(sourceNode), dest(destNode) {
    this->iSource = iSource;
    this->iDest = iDest;
    setAcceptedMouseButtons(Qt::NoButton);
    source->addEdge(this);
    dest->addEdge(this);
    label = QString::number(w);
    this->graph = graph;
    color= Qt::black;
    adjust();
}

Node *Edge::sourceNode() const
{
    return source;
}

Node *Edge::destNode() const
{
    return dest;
}

void Edge::adjust()
{
    if (!source || !dest)
        return;

    QLineF line(mapFromItem(source, qreal(0.), qreal(0.)), mapFromItem(dest, 0, 0));
    qreal length = line.length();
    prepareGeometryChange();

    if (length > qreal(20.)) {
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }

}

QRectF Edge::boundingRect() const
{
    if (!source || !dest)
        return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize + height * 2.5) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if (!source || !dest)
        return;
    qreal dX = destPoint.rx() - sourcePoint.rx();
    qreal dY = destPoint.ry() - sourcePoint.ry();
    qreal distance = sqrt(dX * dX + dY * dY);

    QLineF newLine(sourcePoint, destPoint);

    /* newLine.setLength(newLine.length() - 18); */
    /* Midpoint coordinate */
    QPointF mid = (sourcePoint + destPoint) / 2;

    /* Control point coordinate */ 

    qreal cX = height * (-1 * (dY / distance)) + mid.rx();
    qreal cY = height * (dX / distance) + mid.ry();
    QPointF controlPoint = QPointF(cX, cY);
    if (qFuzzyCompare(newLine.length(), qreal(0.)))
        return;
    // Draw the line itself
    QPen myPen(QPen(this->color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->setPen(myPen);

    /* painter->drawLine(newLine); */
    // Draw the arrows
    double angle = std::atan2(-newLine.dy(), newLine.dx());
    QLineF ghostLine(controlPoint, destPoint);
    ghostLine.setLength(ghostLine.length() - 18);

    QPointF destArrowP1 = destPoint - QPointF(sin(angle + M_PI / 3) * arrowSize,
                                              cos(angle + M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
                                              cos(angle + M_PI - M_PI / 3) * arrowSize);
    QPainterPath myPath;
    myPath.moveTo(sourcePoint);
    myPath.quadTo(controlPoint, ghostLine.p2());
    /* strokePath = myPath; */
    /* painter->drawLine(newLine); */
    painter->strokePath(myPath, myPen);
    painter->setBrush(this->color);
    painter->drawPolygon(QPolygonF() << newLine.p2() << destArrowP1 << destArrowP2);

    painter->drawText(controlPoint, label);
}

void Edge::setColor(QColor q) {
    this->color = q;
}
