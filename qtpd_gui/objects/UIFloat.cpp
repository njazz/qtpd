// (c) 2017 Alex Nadzharov
// License: GPL3

#include "UIFloat.h"

#include "PropertyList.h"

#include <QStyleOptionGraphicsItem>

#include "Preferences.h"

namespace qtpd {

UIFloat::UIFloat()
{

    setSize(35, 20);
    _objectDataModel.setObjectSize(os_FixedHeight, 30, 20);

    deselect();

    setWidth(35);
    setHeight(20);

    resizeEvent();

    setObjectData("0");
}

UIObject* UIFloat::createObj(QString)
{
    UIFloat* ret = new UIFloat();

    return ret;
}

UIObject* UIFloat::createObject(QString, t_canvas*, QGraphicsView* = 0)
{
    return 0;
}

void UIFloat::initProperties()
{
    UIObject::initProperties();

    properties()->create("Value", "Preset", "0.1", 0.);
}

void UIFloat::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget*)
{
    p->setClipRect(option->exposedRect);

    QPolygon poly;
    poly << QPoint(0, 0) << QPoint(width() - 5, 0) << QPoint(width(), 5) << QPoint(width(), height()) << QPoint(0, height());

    p->setPen(QPen(QColor(220, 220, 220), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    QPainterPath tmpPath;
    tmpPath.addPolygon(poly);
    QBrush br = QBrush(QColor(220, 220, 220), Qt::SolidPattern);
    p->fillPath(tmpPath, br);

    if (isSelected()) {
        p->setPen(QPen(QColor(0, 192, 255), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    }

    else {
        p->setPen(QPen(QColor(128, 128, 128), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    }

    p->drawPolygon(poly);

    QTextOption* op = new QTextOption;
    op->setAlignment(Qt::AlignLeft);
    p->setPen(QPen(QColor(0, 0, 0), 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    p->setFont(QFont(PREF_QSTRING("Font"), 11, 0, false));
    p->drawText(2, 3, width() - 2, height() - 3, 0, _objectDataModel.objectData(), 0);
}

void UIFloat::autoResize()
{
    QFont myFont(PREF_QSTRING("Font"), 11);
    QFontMetrics fm(myFont);

    setWidth((int)fm.width(QString("00.00")) + 5); //todo
    if (width() < _objectDataModel.minimumBoxWidth())
        setWidth(_objectDataModel.minimumBoxWidth());
}

///////////////////

void UIFloat::objectPressEvent(QGraphicsSceneMouseEvent* ev)
{

    _startY = ev->pos().y();

    if ((getEditMode() == em_Unlocked)) {
        emit selectBox(this, ev);
        dragOffset = ev->pos().toPoint();
    }
}

void UIFloat::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
{
}

void UIFloat::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    if ((event->buttons() & Qt::LeftButton) && (getEditMode() == em_Unlocked)) {
        emit moveBox(this, event);
    }

    if ((event->buttons() & Qt::LeftButton) && (getEditMode() != em_Unlocked)) {
        //todo fix
        //
        std::string str = std::to_string(::atof(objectData().toStdString().c_str()) - event->pos().y() + _startY);
        setObjectData(str.c_str()); //- startY
        autoResize();
        _startY = event->pos().y();

        QString send = "set " + _objectDataModel.objectData();

        emit sendMessage(this->serverObject(), send);
        emit sendMessage(this->serverObject(), QString("bang "));

        update();
    }

    event->ignore();

    //todo move!
    if (getEditMode() != em_Unlocked) {
        setCursor(QCursor(Qt::UpArrowCursor));
    } else {
        setCursor(QCursor(Qt::ArrowCursor));
    }
}

///////

//void UIFloat::setPdMessage(QString message)
//{
//    setObjectData(message);
//    autoResize();

//    QFont myFont(PREF_QSTRING("Font"), 11);
//    QFontMetrics fm(myFont);
//    int new_w = fm.width(objectData()) + 10;
//    new_w = (new_w < 25) ? 25 : new_w;
//    setWidth(new_w);

//    //temporary
//    //move
//    // TODO-PD_OBJECT
//    //        if (getEditMode() == em_Unlocked) {
//    //            if (!pdObject()) {
//    //                qDebug("msg: bad pd object!");
//    //            } else {

//    //                std::string msg = ("set " + _objectDataModel.objectData().toStdString());
//    //                cmp_sendstring((t_pd*)pdObject(), msg);
//    //            }
//    //        }
//}

void UIFloat::updateUI(AtomList msg)
{
    if (msg.size() > 0) {
        setObjectData(msg.at(0).asString().c_str());
        emit callRepaint();
    }
}

std::string UIFloat::asPdFileString()
{
    // THE fix
    std::string ret;

    ret = "#X obj ";
    ret += std::to_string(x()) + " " + std::to_string(y()) + " ";
    ret += "ui.float ";
    ret += ((objectData() == "") ? ((std::string) "") : (_objectDataModel.objectData().toStdString() + " ")) + properties()->asPdFileString();

    return ret;
}
}
