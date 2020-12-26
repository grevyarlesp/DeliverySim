#include "mainwindow.h"

#include <QApplication>
#include "graphwidget.h" 


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    /* GraphWidget *graphWidget = new GraphWidget; */
    /* w.setCentralWidget(graphWidget); */
    
    w.show();
    return a.exec();
}
