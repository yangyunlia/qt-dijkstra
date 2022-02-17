#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent) {
    QWidget *w = new QWidget();
    setCentralWidget(w);
    setGeometry(200, 200, 800, 600);
    QVBoxLayout *vlayout = new QVBoxLayout();
    QHBoxLayout *head = new QHBoxLayout();
    g = new graph();
    vlayout->addLayout(head, 1);
    QPushButton *randGenerate = new QPushButton("刷新");
    QPushButton *changeDir = new QPushButton("有向图/无向图");
    QPushButton *start = new QPushButton("迪杰斯特拉算法");
    QPushButton *floyd = new QPushButton("弗洛伊德算法");
    head->addWidget(randGenerate);
    head->addWidget(changeDir);
    head->addWidget(start);
    head->addWidget(floyd);
    vlayout->addWidget(g, 10);
    w->setLayout(vlayout);
    QObject::connect(randGenerate, &QPushButton::clicked, this, &MainWindow::reset);
    QObject::connect(changeDir, &QPushButton::clicked, g, &graph::changeDir);
    QObject::connect(start, &QPushButton::clicked, g,&graph::startDijkstra);
    QObject::connect(floyd, &QPushButton::clicked, g,&graph::startFloyd);
}

MainWindow::~MainWindow(){

}

void MainWindow::reset(){
    g->reset();
    g->repaint();
}

void MainWindow::addArc() {
    int s = headNode->text().toInt();
    int t = tailNode->text().toInt();
    int w = weight->text().toInt();
    g->addArc(s, t, w);
    g->repaint();
}

