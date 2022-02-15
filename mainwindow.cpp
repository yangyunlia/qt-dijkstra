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
    QPushButton *randGenerate = new QPushButton("生成图");
    QPushButton *addArc = new QPushButton("添加边");
    QPushButton *start = new QPushButton("开始运行");
    vexNum = new QLineEdit();
    headNode = new QLineEdit();
    tailNode = new QLineEdit();
    weight = new QLineEdit();
    QLabel *l = new QLabel("输入节点数目");
    head->addWidget(l);
    head->addWidget(vexNum);
    head->addWidget(randGenerate);
    head->addWidget(new QLabel("节点1"));
    head->addWidget(headNode);
    head->addWidget(new QLabel("节点2"));
    head->addWidget(tailNode);
    head->addWidget(new QLabel("权重"));
    head->addWidget(weight);
    head->addWidget(addArc);
    head->addWidget(start);
    vlayout->addWidget(g, 10);
    w->setLayout(vlayout);
    QObject::connect(randGenerate, &QPushButton::clicked, this, &MainWindow::randomGraph);
    QObject::connect(addArc, &QPushButton::clicked, this, &MainWindow::addArc);
    QObject::connect(start, &QPushButton::clicked, g,&graph::start);
}

MainWindow::~MainWindow(){

}

void MainWindow::randomGraph() {
    int a = vexNum->text().toInt();
    g->randomGraph(a);
    g->repaint();
}

void MainWindow::addArc() {
    int s = headNode->text().toInt();
    int t = tailNode->text().toInt();
    int w = weight->text().toInt();
    g->addArc(s, t, w);
    g->repaint();
}

