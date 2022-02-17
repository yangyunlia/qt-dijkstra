#include "vexbutton.h"

vexButton::vexButton(int i, QString name):QPushButton(name)
{
    id = i;
}

void vexButton::mousePressEvent(QMouseEvent *e) {
    this->setStyleSheet("background-color: red;border-radius: 20px");
    if(g->pair.size() == 0) {
        g->pair.append(id);
        return;
    }
    int a = g->pair[0];
    g->addArc(a, id, 1);
    g->pair.remove(0);
    g->vlist[a]->setStyleSheet("background-color: blue;border-radius: 20px");
    this->setStyleSheet("background-color: blue;border-radius: 20px");
}
