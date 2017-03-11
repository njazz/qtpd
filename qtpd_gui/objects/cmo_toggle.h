#ifndef CMO_TOGGLE_H
#define CMO_TOGGLE_H

//#include <QWidget>

#include <qlineedit.h>

#include "cm_object.h"
#include "cm_port.h"

#include "cm_pdlink.h"

namespace cm
{

////
/// \brief gui object: message box (ui.msg)
///
class UIToggle : public UIObject
{
    Q_OBJECT

private:
    bool clicked_;

    bool value_;

    //QLineEdit* editor_;

public:
    explicit UIToggle(UIObject *parent = 0);

    static UIObject* createObject(std::string objectData, t_canvas* pdCanvas, UIWidget *parent=0)
    {
        UIToggle* b = new UIToggle((UIObject*)parent);

        b->addInlet();
        b->addOutlet();

        b->setObjectData("");

        std::string message = "ui.msg";

        //temp
        t_object* new_obj = 0 ;
        if (!pdCanvas)
        {qDebug("bad pd canvas instance");}
        else
        {
            QPoint pos = QPoint(0,0);
            new_obj = cmp_create_message(pdCanvas, message, pos.x(), pos.y());
        }

        if (new_obj)
        {
            qDebug ("created msgbox %s | ptr %lu\n",  message.c_str(), (long)new_obj);
            b->setPdObject(new_obj);
        }
        else
        {
            qDebug("Error: no such object %s",  message.c_str());
        }
        //b->setFixedSize(20,20);

        b->setPdMessage("");

        return (UIObject*) b;
    };

    void initProperties()
    {
        UIObject::initProperties();

        this->properties()->create("Value","Preset","0.1",0.);
    }

    void paintEvent(QPaintEvent *)
    {    QPainter p(this);


         if (this->value_)
         {
             float lw = 2;//+this->width()/20.;
             p.setPen(QPen(QColor(0, 192, 255), lw, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
             //p.drawEllipse(QRect(1+lw/2, 1+lw/2, this->width()-2-lw,this->height()-2-lw));
             p.drawLine(2, 2, this->width()-2, this->height()-2);
             p.drawLine(this->width()-2,2,2,this->height()-2);


         }
         //         else
         //         {
         //             p.setPen(QPen(QColor(220, 220, 220), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
         //             p.drawEllipse(QRect(1,1,this->width()-2,this->height()-2));
         //         }


         if (this->isSelected() )
         {
             p.setPen(QPen(QColor(0, 192, 255), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
         }
         else
         {
             p.setPen(QPen(QColor(128, 128, 128), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
         }

          p.drawRect(0,0,this->width(),this->height());



    }

    void resizeEvent(QResizeEvent *event)
    {
        UIObject::resizeEvent(event);
        this->setFixedHeight(this->width());
    }

    ///////////////////

    void mousePressEvent(QMouseEvent *ev)
    {

        //        if ( (this->getEditMode()==em_Unlocked) && this->isSelected())
        //        {
        //            this->editor_->setText(QString(this->getObjectData().c_str()));
        //            this->editor_->show();
        //            this->editor_->setFocus();
        //        }

        //        emit selectBox(this);

        this->dragOffset = ev->pos();


        if (this->getEditMode() != em_Unlocked)
        {
            this->value_ = !this->value_;
            this->repaint();

            if (!this->getPdObject())
            {
                qDebug("msg: bad pd object!");
            }
            else
            {
                //lol
                cmp_sendstring((t_pd*)this->getPdObject(), ((this->value_)?((std::string)"set 1").c_str():((std::string)"set 0").c_str()));

                cmp_sendstring((t_pd*)this->getPdObject(), ((std::string)"bang").c_str());
            }

        }

    }

    void mouseReleaseEvent(QMouseEvent *)
    {
        //this->selected_ = false;

        //if (!this->getEditMode())
        //        {
        //            //this->clicked_ = false;
        //            this->repaint();
        //        }



    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if(event->buttons() & Qt::LeftButton)
        {
            emit moveBox(this, event);
        }
        event->ignore();

        //todo move!
        if (this->getEditMode() != em_Unlocked)
        {
            this->setCursor(QCursor(Qt::PointingHandCursor));
        }
        else
        {
            this->setCursor(QCursor(Qt::ArrowCursor));
        }

    }




    ///////

    void setPdMessage(std::string message)
    {
        this->setObjectData(message);

        //        QFont myFont(PREF_QSTRING("Font"), 11);
        //        QFontMetrics fm(myFont);
        //        int new_w = fm.width(QString(this->getObjectData().c_str())) + 10;
        //        new_w = (new_w<25) ? 25 : new_w;
        //        this->setFixedWidth(new_w);
        //        this->editor_->setFixedWidth(this->width()-5);

        //        //temporary
        //        //move
        //        if (this->getEditMode() == em_Unlocked)
        //        {
        //            if (!this->getPdObject())
        //            {
        //                qDebug("msg: bad pd object!");
        //            }
        //            else
        //            {

        //                //std::string msg = ("set "+ this->getObjectData());
        //                //cmp_sendstring((t_pd*)this->getPdObject(), msg);
        //            }
        //        }
    }

    static void updateUI(void* uiobj, ceammc::AtomList msg)
    {
        qDebug("update ui");
        UIToggle *x = (UIToggle*)uiobj;

        std::string obj_data;
        for (int i=0; i<msg.size();i++)
        {
            obj_data += msg.at(i).asString() + " ";
        }

 //       x->setObjectData(obj_data);

        x->repaint();
    }

    void setPdObject(void *obj)
    {
        UIObject::setPdObject(obj);
        cmp_connectUI((t_pd*)this->getPdObject(), (void*)this, &UIToggle::updateUI);
    }


    std::string getSaveString()
    {return "ui.toggle "+ this->getObjectData();}





};

}

#endif // CMO_MSG_H