#include "buttonhandler.h"

ButtonHandler::ButtonHandler()
{

}

void ButtonHandler::draw(QTextEdit* textEdit, GraphWidget* graphWidget) {
    graphWidget->clear();
    QString text = textEdit->toPlainText();
    int a[3], cnt = 0;
    QStringList l1 = text.split("\n",  QString::SkipEmptyParts);
    QStringList::const_iterator constIterator, constIterator2;
    for (constIterator = l1.constBegin(); constIterator != l1.constEnd(); ++constIterator) {
        QStringList l2 = constIterator->split(" ", QString::SkipEmptyParts);
        for (constIterator2 = l2.constBegin(); constIterator2 != l2.constEnd(); ++constIterator2) {
            /* qDebug() << *constIterator2 << '\n'; */
            a[cnt++] = constIterator2->toInt();
        }
        qDebug() << a[0] << a[1] << a[2];
        if (cnt == 3) {
            cnt = 0;
        }
        graphWidget->addEdge(a[0], a[1], a[2]);
    }
    /* graphWidget->addEdge(1, 2, 3); */
    graphWidget->draw();

}
