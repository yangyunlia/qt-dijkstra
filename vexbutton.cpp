#include "vexbutton.h"
#include<QMouseEvent>
vexButton::vexButton(int i, QString name):QPushButton(name)
{
    id = i;
}

void vexButton::mousePressEvent(QMouseEvent *e) {
    if(e->button() == 1) {
        this->setStyleSheet("background-color: red;border-radius: 20px");
        if(g->pair.size() == 0) {
            g->pair.append(id);
            return;
        }
        int a = g->pair[0];
        g->addArc(a, id, 1);
        g->pair.clear();
        g->vlist[a]->setStyleSheet("background-color: blue;border-radius: 20px");
        this->setStyleSheet("background-color: blue;border-radius: 20px");
    } else {
        g->deleteNode(id);
    }
}

