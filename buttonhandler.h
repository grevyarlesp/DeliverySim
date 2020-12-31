#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include "graphwidget.h"
#include "shortestpath.h"

class ButtonHandler {
public:
    ButtonHandler();
    void draw(QTextEdit* textEdit, GraphWidget* graphWidget);
    void calculatePath(QTextEdit* textEdit, GraphWidget* graphWidget);
};

#endif // BUTTONHANDLER_H
