#ifndef VEXBUTTON_H
#define VEXBUTTON_H
#include "graph.h"
#include <QPushButton>
class vexButton:public QPushButton
{
public:
    graph *g;
    int id;
    vexButton(int i, QString name);
    void mousePressEvent(QMouseEvent *e);
};

#endif // VEXBUTTON_H
