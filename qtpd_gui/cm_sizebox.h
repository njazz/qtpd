#ifndef CM_SIZEBOX_H
#define CM_SIZEBOX_H

#include "cm_widget.h"

#include <QPainter>

class cm_sizebox : public cm_widget
{
public:
    //cm_sizebox();
    explicit cm_sizebox(cm_widget *parent = 0);


    void paintEvent(QPaintEvent*)   //QPaintEvent *pe
    {    QPainter p(this);

         //p.setRenderHint(QPainter::SmoothPixmapTransform,true);
         p.setPen(QPen(QColor(128, 128, 128), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
         p.drawRect(0,0,this->width(),this->height());

//           if (this->hover)
//           {
//               p.setPen(QPen(QColor(192, 192, 192), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
//               p.drawRect(0,0,this->width(),this->height());
//           }

    }

};

#endif // CM_SIZEBOX_H
