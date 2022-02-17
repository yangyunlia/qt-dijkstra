#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include <QLineEdit>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    graph *g;
    QLineEdit *vexNum;
    QLineEdit *headNode;
    QLineEdit *tailNode;
    QLineEdit *weight;
    void reset();
    void addArc();
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
