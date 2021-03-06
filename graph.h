#ifndef GRAPH_H
#define GRAPH_H

#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QTimer>
#include <QThread>
#include<QPushButton>
#include<QMainWindow>
#include<QLineEdit>
#include<QEventLoop>
class graph : public QWidget
{
    Q_OBJECT
public:
    class thread *t;
    int **matrix;
    int vexNum;
    int arcNum;
    int *flag;
    int *path;
    int *dis;
    int **d;
    int **fpath;
    int k;
    int dijkstraOrFloyd;
    int isDir;
    QLineEdit *inputLine;
    QGridLayout *layout;
    QWidget *w;
    QEventLoop *loop;
    QList<QPushButton *> vlist;
    QList<int> pair;
    QMainWindow *inputW;
    void startDijkstra();
    void startFloyd();
    explicit graph(QWidget *parent = nullptr);
    void reset();
    void changeDir();
    void addArc(int a, int b, int w);
    void dijkstra();
    void floyd();
    void paintEvent(QPaintEvent *event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void deleteNode(int id);
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
            if(g->dijkstraOrFloyd == 0) {
                g->dijkstra();
            } else {
                g->floyd();
            }
            QThread::sleep(3);
        }
    }
};
#endif // GRAPH_H
