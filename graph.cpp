#include "graph.h"
#include<QPainter>
#include<QHBoxLayout>
#include<QLabel>
graph::graph(QWidget *parent) : QWidget{parent} {
    flag = nullptr;
    path = nullptr;
    dis = nullptr;
    t = new class thread(this);
    QHBoxLayout *h = new QHBoxLayout();
    w = new QWidget();
    layout = new QGridLayout();
    h->addWidget(w, 1);
    h->addLayout(layout, 1);
    setLayout(h);
}

void graph::randomGraph(int vN) {
    vexNum = vN;
    arcNum = vN;
    position = new int*[vN];
    matrix = new int*[vN];
    flag = nullptr;
    path = nullptr;
    dis = nullptr;
    for(int i = 0;i < vN; i++) {
        matrix[i] = new int[vN];
        for(int j = 0;j < vN;j++) {
            matrix[i][j] = 0;
        }
        position[i] = new int[2];
        for(int j = 0;j < 2; j++) {
            position[i][j] = rand()%100;
        }
    }
}

void graph::addArc(int a, int b, int w){
    if(a < 0 || a >= vexNum || b < 0|| b >= vexNum) {
        return;
    }
    matrix[a][b] = w;
    matrix[b][a] = w;
}

void graph::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  if(flag != nullptr) {
        painter.drawText(this->width()/2+50, this->height()/2, "节点 路径 长度");
  }
  for(int i = 0; i < vexNum; i++) {
      int x = int(position[i][0]*double(this->width()/2-100)/100);
      int y = int(position[i][1]*double(this->height()-100)/100);
      if(flag != nullptr && flag[i]  == 1) {
          QColor c(0,0xff,0);
          QPen p(c);
          painter.setPen(p);
      }
      painter.drawEllipse(x, y, 20, 20);
      painter.drawText(x + 8, y + 12, QString::number(i, 10));
      QColor c(0, 0,0);
      QPen p(c);
      painter.setPen(p);
      for(int j = 0; j < vexNum; j++) {
          if(matrix[i][j] != 0) {
              int x1 = int(position[j][0]*double(this->width()/2 - 100)/100);
              int y1 = int(position[j][1]*double(this->height() -100)/100);
              painter.drawLine(x+8, y + 12, x1 + 8, y1 + 12);
          }
      }
      for(int i = 0;i < vexNum; i++) {
          for(int j = 0;j < vexNum; j++) {
              int x = this->width()/2 + 50 + j *20;
              int y = i*20 + 50;
              painter.drawText(x, y, QString::number(matrix[i][j], 10));
          }
      }
      if(flag != nullptr) {
          painter.drawText(this->width()/2 + 50, this->height()/2+(i + 1)*20, QString::number(i, 10)+"   "+QString::number(path[i], 10)+"   "+QString::number(dis[i], 10));
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

void graph::start() {
    t->start();
}
