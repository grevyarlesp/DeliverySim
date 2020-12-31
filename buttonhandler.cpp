#include "buttonhandler.h"

ButtonHandler::ButtonHandler() {

}

void ButtonHandler::draw(QTextEdit* textEdit, GraphWidget* graphWidget) {
    graphWidget->clear();
    QString text = textEdit->toPlainText();
    QVector<int> a(3);
    int cnt = 0;
    QStringList l1 = text.split("\n",  QString::SkipEmptyParts);
    QStringList::const_iterator constIterator, constIterator2;
    for (constIterator = l1.constBegin(); constIterator != l1.constEnd(); ++constIterator) {
        QStringList l2 = constIterator->split(" ", QString::SkipEmptyParts);
        for (constIterator2 = l2.constBegin(); constIterator2 != l2.constEnd(); ++constIterator2) {
            a[cnt++] = constIterator2->toInt();
        }
        qDebug() << a[0] << a[1] << a[2];
        if (cnt == 4) {
            cnt = 0;
        }
        graphWidget->addEdge(a[0], a[1], a[2], a[3]);
    }
    /* graphWidget->addEdge(1, 2, 3); */
    graphWidget->draw();
}

void ButtonHandler::calculatePath(QTextEdit* textEdit, GraphWidget* graphWidget) {
    QString text = textEdit->toPlainText();
    QVector<int> a(3);
    int cnt = 0;
    graphWidget->resetColor();
    QStringList l1 = text.split(" ",  QString::SkipEmptyParts);
    QStringList::const_iterator constIterator;
    for (constIterator = l1.constBegin(); constIterator != l1.constEnd(); ++constIterator) {
        a[cnt++] = constIterator->toInt();
    }
    ShortestPath sp(graphWidget->getGraph(), graphWidget); 
    qDebug() << "Calculator: " << a[1] << a[2] << a[0];
    sp.execute(a[1], a[2], a[0], true);
}
