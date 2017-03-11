#ifndef CM_PORT_H
#define CM_PORT_H

#include <QWidget>

#include <QtGui>

#include "cm_widget.h"

namespace cm
{

////
/// \brief gui representation of t_inlet / t_outlet
///
class Port : public UIWidget
{
    Q_OBJECT

private:
    bool hover;
public:
    int portIndex;

    enum {portInlet, portOutlet} portType;

    explicit Port(UIWidget *parent = 0);

    void paintEvent(QPaintEvent*)   //QPaintEvent *pe
    {    QPainter p(this);

         //p.setRenderHint(QPainter::SmoothPixmapTransform,true);
         p.setPen(QPen(QColor(128, 128, 128), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

          p.drawRect(0,0,this->width(),this->height());

           if (this->hover)
           {
               p.setPen(QPen(QColor(255, 128, 0), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
               p.drawRect(0,0,this->width(),this->height());
           }

    }

    void enterEvent(QEvent *)
    {
        if (this->getEditMode() == em_Unlocked)
        {
            this->hover = true;
            this->repaint();

            emit mouseEntered();
        }

    }
    void leaveEvent(QEvent *)
    {
        if (this->getEditMode() == em_Unlocked)
        {
            this->hover = false;
            this->repaint();

            emit mouseLeaved();
        }

    }

    void mousePressEvent(QMouseEvent *ev)
    {
        if (this->getEditMode() == em_Unlocked)
        {

        emit mousePressed(this,ev);
        }
    }

    void mouseReleaseEvent(QMouseEvent *ev)
    {
        if (this->getEditMode() == em_Unlocked)
        {
        emit mouseReleased(this,ev);
        }
    }



public slots:
};

}

#endif // CM_PORT_H