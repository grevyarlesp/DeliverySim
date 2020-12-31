#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "graphwidget.h"
#include <QDebug>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include "buttonhandler.h"
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButton();
    void handleCalculateButton();
    void importActionTrigger();
    void requestActionTrigger();
private:
    /* Ui::MainWindow *ui; */
    GraphWidget *graphWidget;
    ButtonHandler* buttonHandler;
    QPushButton *drawButton, *calculateButton;
    QTextEdit *textEdit, *requestEdit;
    void setupUi(QWidget *parent);
    void setupMenuBar(QWidget* parent);
    void setupLeftWidget(QWidget* parent);
};
#endif // MAINWINDOW_H
