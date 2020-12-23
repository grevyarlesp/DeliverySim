#include "mainwindow.h"
#include "ui_mainwindow.h"


/* TODO: Create a new class, ButtonHandler to handle button clicks */
/* TODO: Create a new class, ActionHandler to handle action */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    buttonHandler = new ButtonHandler;
    QWidget* widget = new QWidget(this);
    setCentralWidget(widget);
    qDebug() << this->size().width() << ' ' << this->size().height() << '\n';
    QHBoxLayout *layout = new QHBoxLayout;

    QWidget* widget2 = new QWidget(widget);

    QVBoxLayout *subLayout = new QVBoxLayout;

    graphWidget = new GraphWidget(this);
    /* graphWidget->setStyleSheet("border: 1px solid red"); */

    textEdit = new QTextEdit(widget2);
    drawButton = new QPushButton("Draw", widget2);
    subLayout->addWidget(textEdit);
    subLayout->addWidget(drawButton);


    layout->addWidget(widget2, 2);
    layout->addWidget(graphWidget, 8);
    /* layout->addWidget(widget2, 8); */
    widget->setLayout(layout);
    widget2->setLayout(subLayout);
    graphWidget->addEdge(2, 3, 4);
    graphWidget->addEdge(1, 3, 4);
    graphWidget->addEdge(1, 4, 4);
    graphWidget->addEdge(2, 4, 4);

    setupMenuBar(parent);

    connect(drawButton, &QPushButton::released, this, &MainWindow::handleButton);
}

void MainWindow::setupMenuBar(QWidget *parent) {
    QMenuBar *menuBar = new QMenuBar(parent);
    this->setMenuBar(menuBar);
    QMenu * fileMenu = this->menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(new QAction("Import graph from street.txt"));
    /* fileMenu->addAction(newAct); */
}

void MainWindow::setupLeftWidget(QWidget *parent) {
    /* lineEdit = new QLineEdit(parent); */
    textEdit = new QTextEdit(parent);
}

MainWindow::~MainWindow()
{
    /* delete ui; */
}

void MainWindow::handleButton() {
    buttonHandler->draw(textEdit, graphWidget);
    
}
