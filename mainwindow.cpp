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
    requestEdit = new QTextEdit(widget2);
    calculateButton = new QPushButton("Calculate", widget2);
    subLayout->addWidget(textEdit);
    subLayout->addWidget(drawButton);
    subLayout->addWidget(requestEdit);
    subLayout->addWidget(calculateButton);
    layout->addWidget(widget2, 2);
    layout->addWidget(graphWidget, 8);

    /* layout->addWidget(widget2, 8); */
    widget->setLayout(layout);
    widget2->setLayout(subLayout);

    setupMenuBar(parent);

    connect(drawButton, &QPushButton::released, this, &MainWindow::handleButton);
    connect(calculateButton, &QPushButton::released, this, &MainWindow::handleCalculateButton);
    graphWidget->draw();
}

void MainWindow::setupMenuBar(QWidget *parent) {
    QMenuBar *menuBar = new QMenuBar(parent);
    this->setMenuBar(menuBar);
    QMenu * fileMenu = this->menuBar()->addMenu(tr("&File"));
    QAction* importAction = new QAction("Import graph from street.txt and transport_type.txt");
    QAction* requestAction = new QAction("Import query from query.txt");
    fileMenu->addAction(importAction);
    fileMenu->addAction(requestAction);
    connect(importAction, &QAction::triggered, this, &MainWindow::importActionTrigger);
    connect(requestAction, &QAction::triggered, this, &MainWindow::requestActionTrigger);
}

MainWindow::~MainWindow()
{
    /* delete ui; */
}

void MainWindow::handleButton() {
    buttonHandler->draw(textEdit, graphWidget);
}

void MainWindow::handleCalculateButton() {
    buttonHandler->calculatePath(requestEdit, graphWidget);
}

void MainWindow::importActionTrigger() {
    textEdit->clear();
    graphWidget->clear();
    ifstream ifs1("street.txt");
    ifstream ifs2("transport_type.txt");
    if (! ifs1 || ! ifs2) return;
    int n;
    int w, allow;
    ifs1 >> n;
    ifs2 >> n;
    QString text;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            ifs1 >> w;
            ifs2 >> allow;
            if (w == 0) continue;
            graphWidget->addEdge(i, j, w, allow);
            text.append(QString::number(i) + " " + QString::number(j) + " " + QString::number(w) + " " + QString::number(allow) + "\n");
        }
    }
    textEdit->setText(text);
    ifs1.close();
    ifs2.close();
    return;

}

void MainWindow::requestActionTrigger() {
    requestEdit->clear();
    QString text;
    ifstream ifs("query.txt");
    if (! ifs) return;
    int allow, u, v;
    ifs >> allow >> u >> v;
    text.append(QString::number(allow) + " " + QString::number(u) + " " + QString::number(v));
    ifs.close();
    requestEdit->setText(text);
}
