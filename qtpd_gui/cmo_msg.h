#ifndef CMO_MSG_H
#define CMO_MSG_H

//#include <QWidget>

#include <qlineedit.h>

#include "cm_object.h"
#include "cm_port.h"

#include "cm_pdlink.h"


////
/// \brief gui object: message box (ui.msg)
///
class cmo_msg : public cm_object
{
    Q_OBJECT

private:
    bool clicked_;

    QLineEdit* editor_;

public:
    explicit cmo_msg(cm_object *parent = 0);

    void paintEvent(QPaintEvent *)
    {    QPainter p(this);


         QPolygon poly;
          poly << QPoint(0,0) <<
                  QPoint(this->width(),0) <<
                  QPoint(this->width()-4,4) <<
                  QPoint(this->width()-4,this->height()-4) <<
                  QPoint(this->width(),this->height()) <<
                  QPoint(0,this->height());


           //p.drawRect(0,0,this->width(),this->height());

           p.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
            QPainterPath tmpPath;
             tmpPath.addPolygon(poly);
              QBrush br = QBrush(QColor(220,220,220), Qt::SolidPattern);
               p.fillPath(tmpPath,br);

                if (this->isSelected() )
                {
                    p.setPen(QPen(QColor(0, 192, 255), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
                }
                else
                if (this->clicked_)
                {
                    p.setPen(QPen(QColor(0, 192, 255), 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                }
                else
                {
                    p.setPen(QPen(QColor(128, 128, 128), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
                }

                 p.drawPolygon(poly);


                  QTextOption *op = new QTextOption;
                   op->setAlignment(Qt::AlignLeft);
                    p.setPen(QPen(QColor(0, 0, 0), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

                     p.setFont(QFont("Monaco",11,0,false));
                      p.drawText(2,3,this->width()-2,this->height()-3,0,this->getObjectData().c_str(),0);


    }


    ///////////////////

    void mousePressEvent(QMouseEvent *ev)
    {

        if ( (this->getEditMode()==em_Unlocked) && this->isSelected())
        {
            this->editor_->setText(QString(this->getObjectData().c_str()));
            this->editor_->show();
            this->editor_->setFocus();
        }

        emit selectBox(this);
        this->dragOffset = ev->pos();

        if (!(this->getEditMode()==em_Unlocked))
        {
            this->clicked_ = true;
            this->repaint();

            //todo timer
        }

        //temporary
        //move
        if (this->getEditMode() != em_Unlocked)
        {
            if (!this->getPdObject())
            {
                qDebug("msg: bad pd object!");
            }
            else
            {

                std::string msg = ("list "+ this->getObjectData());
                //qDebug("send msg %s", msg.c_str());

                cmp_sendstring((t_pd*)this->getPdObject(), ((std::string)"bang").c_str());
            }

        }

    }

    void mouseReleaseEvent(QMouseEvent *)
    {
        //this->selected_ = false;

        //if (!this->getEditMode())
        {
            this->clicked_ = false;
            this->repaint();
        }



    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if(event->buttons() & Qt::LeftButton)
        {
            emit moveBox(this, event);
        }
        event->ignore();

    }


    ///////

    void setPdMessage(std::string message)
    {
        this->setObjectData(message);

        QFont myFont("Monaco", 11);
        QFontMetrics fm(myFont);
        int new_w = fm.width(QString(this->getObjectData().c_str())) + 10;
        new_w = (new_w<25) ? 25 : new_w;
        this->setFixedWidth(new_w);
        this->editor_->setFixedWidth(this->width()-5);

        //temporary
        //move
        if (this->getEditMode() == em_Unlocked)
        {
            if (!this->getPdObject())
            {
                qDebug("msg: bad pd object!");
            }
            else
            {

                std::string msg = ("set "+ this->getObjectData());
                //qDebug("send msg %s", msg.c_str());
                cmp_sendstring((t_pd*)this->getPdObject(), msg.c_str());
            }

        }



    }



signals:
    //void selectBox(cm_widget*box);
private slots:
    void editorDone();
    void editorChanged();

};


#endif // CMO_MSG_H