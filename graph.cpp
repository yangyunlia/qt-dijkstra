#include "graph.h"
#include<QPainter>
#include<QHBoxLayout>
#include<QLabel>
#include<QMouseEvent>
#include<QPushButton>
#include "vexbutton.h"
#include <math.h>
graph::graph(QWidget *parent) : QWidget{parent} {
    flag = nullptr;
    path = nullptr;
    dis = nullptr;
    matrix = nullptr;
    isDir = 0;
    k = 0;
    t = new class thread(this);
    fpath = nullptr;
    d = nullptr;
    dijkstraOrFloyd = 0;
    QHBoxLayout *h = new QHBoxLayout();
    w = new QWidget();
    layout = new QGridLayout();
    h->addWidget(w, 1);
    h->addLayout(layout, 1);
    setLayout(h);
}


void graph::reset() {
    vexNum = 0;
    arcNum = 0;
    matrix = nullptr;
    flag = nullptr;
    path = nullptr;
    dis = nullptr;
    d = nullptr;
    fpath = nullptr;
    k = 0;
    for(int i = 0; i < vlist.size(); i++) {
        vlist[i]->setParent(nullptr);
        vlist[i]->deleteLater();
        delete vlist[i];
    }
    vlist.clear();
}

void graph::mouseDoubleClickEvent(QMouseEvent* e) {
   vexButton *b = new vexButton(vlist.size(), QString::number(vlist.size(), 10));
   b->setStyleSheet("border-radius:20px;background-color: blue");
   b->setGeometry(e->position().x(), e->position().y(), 40, 40);
   b->setParent(this);
   b->show();
   b->g = this;
   vlist.append(b);
   if(vlist.size() == 1) {
       vexNum = 1;
       matrix = new int*[1];
       matrix[0] = new int[1];
       matrix[0][0] = 0;
       return;
   }
   vexNum++;
   int **newMatrix = new int*[vexNum];
   for(int i = 0; i < vexNum - 1; i++) {
       newMatrix[i] = new int[vexNum];
       for(int j = 0;j < vexNum -1; j++) {
           newMatrix[i][j] = matrix[i][j];
       }
   }
   newMatrix[vexNum-1] = new int[vexNum];
   for(int i = 0;i < vexNum; i++) {
       newMatrix[i][vexNum-1] = 0;
       newMatrix[vexNum-1][i] = 0;
   }
   for(int i = 0; i < vexNum-1; i++) {
       delete []matrix[i];
   }
   delete []matrix;
   matrix = newMatrix;
}

void graph::addArc(int a, int b, int w){
    if(a < 0 || a >= vexNum || b < 0|| b >= vexNum) {
        return;
    }
    matrix[a][b] = w;
    if(isDir == 0) {
        matrix[b][a] = w;
    }
    this->repaint();
}
void graph::changeDir() {
    isDir = 1- isDir;
    this->repaint();
}

void graph::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  if(isDir == 0) {
      painter.drawText(20,20, "无向图");
  } else {
      painter.drawText(20,20, "有向图");
  }
  if(flag != nullptr) {
        painter.drawText(this->width()/2+50, this->height()/2, "节点 路径 长度");
  }
  for(int i = 0; i < vexNum; i++) {
      int x = vlist[i]->pos().x() + 8;
      int y = vlist[i]->pos().y() + 8;
      for(int j = 0; j < vexNum; j++) {
          if(matrix[i][j] != 0 && i != j) {
              int x1 = vlist[j]->pos().x() + 8;
              int y1 = vlist[j]->pos().y() + 8;
              painter.drawLine(x, y, x1, y1);
              if(isDir == 1) {
                  x1 = (x1 + x)/2;
                  y1 = (y1 + y)/2;
                  double ya = y - y1;
                  double xa = x1 -x;
                  double ta = atan2(ya, xa);
                  double t1 = ta-acos(-1)/4;
                  double xo1 = x1 - 10*cos(t1);
                  double yo1 = y1 + 10*sin(t1);
                  double t2 = ta + acos(-1)/4;
                  double xo2 = x1 - 10*cos(t2);
                  double yo2 = y1 + 10*sin(t2);
                  painter.drawLine(x1, y1, xo1, yo1);
                  painter.drawLine(x1, y1, xo2, yo2);
              }
          }
      }
      for(int i = 0;i < vexNum; i++) {
          for(int j = 0;j < vexNum; j++) {
              int x = this->width()/2 + 50 + j *20;
              int y = i*20 + 50;
              painter.drawText(x, y, QString::number(matrix[i][j], 10));
          }
      }
      if(dijkstraOrFloyd == 0) {
          if(flag != nullptr && flag[i] == 1) {
              painter.drawText(this->width()/2 + 50, this->height()/2+(i + 1)*20, QString::number(i, 10)+"   "+QString::number(path[i], 10)+"   "+QString::number(dis[i], 10));
          }
      }
  }
  if(dijkstraOrFloyd == 1 && d != nullptr) {
      painter.drawText(this->width()/2 +50, this->height()/2, "距离矩阵d" + QString::number(k, 10));
      painter.drawText(this->width()*3/4 +50, this->height()/2, "路径矩阵d" + QString::number(k, 10));
      for(int i = 0; i < vexNum; i++) {
          for(int j = 0;j < vexNum; j++) {
              painter.drawText(this->width()/2 +50 + 20*j, this->height()/2+(i+1)*20, QString::number(d[i][j], 10));
              painter.drawText(this->width()*3/4 +50 + 20*j, this->height()/2+(i+1)*20, QString::number(fpath[i][j], 10));
          }
      }
  }
}

void graph::dijkstra() {
    if(flag == nullptr) {
        flag = new int[vexNum];
        path = new int[vexNum];
        dis = new int[vexNum];
        for(int i = 0;i < vexNum; i++) {
            if(matrix[0][i] != 0) {
                dis[i] = matrix[0][i];
            } else {
                dis[i] = - 1;
            }
            flag[i] = 0;
            path[i] = 0;
        }
        flag[0] = 1;
        dis[0] = 0;
        path[0] = -1;
        return;
    }
    int minId = -1;
    int minDis = 1<<30;
    for(int i = 0; i < vexNum; i++) {
        if(flag[i] == 0 && dis[i] != - 1 && (dis[i] <minDis)) {
            minDis = dis[i];
            minId = i;
        }
    }
    if(minId == -1) {
        return;
    }
    flag[minId] = 1;
    for(int i = 0; i < vexNum; i++) {
        if(matrix[minId][i] != 0 && (dis[i] == -1|| minDis + matrix[minId][i] < dis[i])) {
            dis[i] = minDis + matrix[minId][i];
            path[i] = minId;
        }
    }
    this->repaint();
}

void graph::floyd() {
    if(d == nullptr) {
        d = new int*[vexNum];
        fpath = new int*[vexNum];
        for(int i = 0;i < vexNum; i++) {
            d[i] = new int[vexNum];
            fpath[i] = new int[vexNum];
            for(int j = 0; j < vexNum; j++){
                if(i == j) {
                    d[i][j] = 0;
                    fpath[i][j] = -1;
                } else if(matrix[i][j] == 0) {
                    d[i][j] = -1;
                    fpath[i][j] = -1;
                } else{
                    fpath[i][j] = i;
                    d[i][j] = matrix[i][j];
                }
            }
        }
        return;
    }

    for(int i = 0;i < vexNum; i++) {
        for(int j = 0;j < vexNum; j++) {
            if(i != k && j != k && d[i][k] != -1 && d[k][j] != -1 && (d[i][k] + d[k][j] < d[i][j] || d[i][j] == -1)) {
                d[i][j] = d[i][k] + d[k][j];
                fpath[i][j] = fpath[k][j];
            }
        }
    }
    k++;
    this->repaint();
}

void graph::startDijkstra() {
    dijkstraOrFloyd = 0;
    t->start();
}

void graph::startFloyd() {
    dijkstraOrFloyd = 1;
    t->start();
}
