// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_ARRAY_H
#define CM_ARRAY_H

#include <QGraphicsView>
#include <QLineEdit>
#include <QMainWindow>
#include <QtGui>

#include "Port.h"
#include "UIObject.h"

//lazy way
//todo proper pattern
#include "OpenFileProxy.h"

#include "UIArrayEditor.h"

namespace qtpd {

////
/// \brief gui object: array box (ui.array)
///
class UIArray : public UIObject {

    Q_OBJECT

private:
    UIArrayEditor _editor;

public:
    explicit UIArray(); //UIObject* parent = 0);

    static UIObject* createObject(QString objectData, t_canvas* pdCanvas, QGraphicsView* parent = 0)
    {
        UIArray* b = new UIArray();
        b->setCanvas((void*)parent);

        //truncate "ui.obj". todo cleanup
        QStringList list = QString(objectData).split(" ");

        //const char* obj_name = objectData.toStdString().c_str();

        std::string data1 = b->properties()->extractFromPdFileString(objectData.toStdString()); //test

        // todo cleanup
        b->setObjectData(data1);
        b->autoResize();

        if (!pdCanvas) {
            qDebug("bad pd canvas instance");
            b->setErrorBox(true);
        } else {
            if (list.size() < 3) {
                b->setErrorBox(true);
            } else {

                t_symbol* name = gensym(list.at(1).toStdString().c_str());
                t_floatarg size = list.at(2).toFloat();

                b->_editor.setPdArray(cmp_new_array(pdCanvas, name, size, 1, 1));
                b->_editor.setWindowTitle("array: " + list.at(1));
            }
        }

        return (UIObject*)b;
    };

    void initProperties()
    {
        UIObject::initProperties();
        properties()->create("ArraySize", "Array", "0.1", 100);
    }

    ////
    /// \brief paint event
    ///
    virtual void paint(QPainter* p, const QStyleOptionGraphicsItem*, QWidget*)
    {
        QBrush brush(bgColor());
        p->setBrush(brush);
        p->drawRect(boundingRect());
        p->setBrush(QBrush());

        p->setRenderHint(QPainter::HighQualityAntialiasing, true);
        p->scale(scale(), scale());

        p->setPen(QPen(QColor(192, 255, 0), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
        p->drawRect(0, 1, width(), height() - 2);

        //remove this later
        if (subpatchWindow()) {
            p->setPen(QPen(QColor(192, 192, 192), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
            p->drawRect(0, 2, width(), height() - 4);
        }

        QColor rectColor = (errorBox()) ? QColor(255, 0, 0) : QColor(128, 128, 128);
        p->setPen(QPen(rectColor, 1, (errorBox()) ? Qt::DashLine : Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
        p->drawRect(0, 0, width(), height());
        QTextOption* op = new QTextOption;
        op->setAlignment(Qt::AlignLeft);
        p->setPen(QPen(QColor(0, 0, 0), 2, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

        p->setFont(QFont(PREF_QSTRING("Font"), 11, 0, false));
        p->drawText(2, 3, width() - 2, height() - 3, 0, objectData().c_str(), 0);

        if (isSelected()) {
            p->setPen(QPen(QColor(0, 192, 255), 1, (errorBox()) ? Qt::DashLine : Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
            p->drawRect(0, 0, width(), height());
        }
    }

    ////
    /// \brief mouse down
    /// \param ev
    ///
    void mousePressEvent(QGraphicsSceneMouseEvent* ev)
    {
        //context menu
        if (ev->button() == Qt::RightButton) {
            //QPoint pos = mapToGlobal(ev->pos());
            //showPopupMenu(pos);
            ev->accept();
            return;
        }

        if ((getEditMode() == em_Unlocked) && isSelected()) {

            emit editObject(this);
            return;
        }

        if ((getEditMode() != em_Unlocked)) {
            if (!errorBox())
                _editor.show();
        }

        emit selectBox(this, ev);
        dragOffset = ev->pos().toPoint();
    }

    ////
    /// \brief mouse up
    ///
    void mouseReleaseEvent(QGraphicsSceneMouseEvent*) {}

    ////
    /// \brief mouse move
    /// \param event
    ///
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event)
    {
        if (event->buttons() & Qt::LeftButton) {
            emit moveBox(this, event);
        }
        event->ignore();

        if ((getEditMode() != em_Unlocked) && (subpatchWindow())) {
            setCursor(QCursor(Qt::PointingHandCursor));
        } else {
            setCursor(QCursor(Qt::ArrowCursor));
        }
    }

    void setPdMessage(std::string message)
    {
        setObjectData(message);
        autoResize();

        QFont myFont(PREF_QSTRING("Font"), 11);
        QFontMetrics fm(myFont);
        int new_w = fm.width(QString(objectData().c_str())) + 10;
        new_w = (new_w < 25) ? 25 : new_w;
        setWidth(new_w);
        //
        setInletsPos();
        setOutletsPos();
    }

signals:

    void mouseMoved();
    void rightClicked();
};
}

#endif // CM_BOX_H