#ifndef BUTTONHANDLER_H
#define BUTTONHANDLER_H

#include <QObject>
#include <QPushButton>
#include <QTextEdit>
#include "graphwidget.h"

class ButtonHandler : public QObject
{
public:
    ButtonHandler();
public: 
    void draw(QTextEdit* textEdit, GraphWidget* graphWidget);
};

#endif // BUTTONHANDLER_H
