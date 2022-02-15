#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <QThread>
class graph : public QWidget
{
    Q_OBJECT
public:
    class thread *t;
    int **matrix;
    int vexNum;
    int arcNum;
    int **position;
    int *flag;
    int *path;
    int *dis;
    QGridLayout *layout;
    QWidget *w;
    void start();
    explicit graph(QWidget *parent = nullptr);
    void randomGraph(int vN);
    void addArc(int a, int b, int w);
    void dijkstra();
    void paintEvent(QPaintEvent *event);
signals:

};
class thread: public QThread {
public:
    graph *g;
    thread(graph *a)  {
        g = a;
    }
    void run() {
        for(int i = 0; i < g->vexNum; i++) {
            g->dijkstra();
            QThread::sleep(3);
        }
    }
};
#endif // GRAPH_H
