// (c) 2017 Alex Nadzharov
// License: GPL3

#include "UILink.h"

#include <QGraphicsProxyWidget>

namespace tilde {
UILink::UILink()
{
    setSize(65, 20);

    initProperties();

    deselect();
    _clicked = false;

    objectData()->setObjectSize(os_FixedHeight, 80, 20);

    resizeEvent();
}

UIObject* UILink::createObj(QString data)
{
    UILink* ret = new UILink();

    ret->fromQString(data);

    return ret;
}

void UILink::paint(QPainter* p, const QStyleOptionGraphicsItem* option, QWidget*)
{
    p->setClipRect(option->exposedRect);

    // does it need a background?

    //        QBrush brush(bgColor());
    //        p->setBrush(brush);
    //        p->drawRect(boundingRect());
    //        p->setBrush(QBrush());

    if (getEditMode() == em_Unlocked) {
        if (isSelected()) {
            p->setPen(QPen(QColor(0, 192, 255), 1, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));
        } else if (_clicked) {
            p->setPen(QPen(QColor(0, 192, 255), 2, Qt::DotLine, Qt::RoundCap, Qt::RoundJoin));
        } else {
            p->setPen(QPen(QColor(128, 128, 128), 1, Qt::DotLine, Qt::SquareCap, Qt::BevelJoin));
        }

        p->drawRect(0, 0, width(), height());
    }

    QTextOption* op = new QTextOption;
    op->setAlignment(Qt::AlignLeft);
    QColor textColor = (hover()) ? QColor(0, 192, 255) : QColor(0, 0, 0);
    p->setPen(QPen(textColor, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    int fontSize = properties()->get("FontSize")->asQString().toInt();
    QFont font = QFont(PREF_QSTRING("Font"), fontSize, 0, false);
    font.setItalic(true);
    p->setFont(font);

    QString text = properties()->get("Title")->asQString();
    p->drawText(2, 3, width() - 2, height() - 3, 0, text, 0);
}

// -----

void UILink::initProperties()
{
    //qDebug() << "properties init";
    UIObject::initProperties();
    QString list = "-";

    properties()->create("Title", "Data", "0.1", list);
    properties()->create("Url", "Data", "0.1", list);
};

void UILink::hoverEnterEvent(QGraphicsSceneHoverEvent*)
{
    if (getEditMode() == em_Unlocked) {
        setHover(true);
        update();
    }
}

void UILink::hoverLeaveEvent(QGraphicsSceneHoverEvent*)
{
    if (getEditMode() == em_Unlocked) {
        setHover(false);
        update();
    }
}

void UILink::objectPressEvent(QGraphicsSceneMouseEvent* ev)
{

    dragOffset = ev->pos().toPoint();

    if (!(getEditMode() == em_Unlocked)) {
        //action
    }
}

void UILink::objectReleaseEvent(QGraphicsSceneMouseEvent*)
{
    _clicked = false;
    update();
}

void UILink::autoResize()
{
    int fontSize = properties()->get("FontSize")->asQString().toInt();

    QFont myFont(PREF_QSTRING("Font"), fontSize);
    QFontMetrics fm(myFont);

    setWidth((int)fm.width(_objectText) + 5);
    if (width() < objectData()->minimumBoxWidth())
        setWidth(objectData()->minimumBoxWidth());

    //duplicate?
    int new_w = fm.width(_objectText) + 20;
    new_w = (new_w < 25) ? 25 : new_w;

    int new_h = fm.boundingRect(QRect(0, 0, new_w, 100), 0, _objectText).height() + 7;

    new_h = (new_h < 25) ? 25 : new_h;

    setWidth(new_w);
    setHeight(new_h);
}

///////

void UILink::fromQString(QString objData) //setPdMessage(std::string message)
{
    //setObjectData("ui.text");

    //TODO temporary fix!
    //        QString msg = objData; //QString(message.c_str());
    //        QStringList list = msg.split("\n");
    //        for (int i = 0; i < list.size(); i++) {
    //            list[i] = list[i] + "\\n";
    //        }

    //        PROPERTY_SET("Text", list.join("\n"));

    //        QString data = properties()->get("Text")->asQString().split("\\n ").join("\n");

    _objectText = objData;

    autoResize();
}

 void UILink::updateUI(AtomList* msg)
{
    std::string obj_data;
    for (size_t i = 0; i < msg->size(); i++) {
        obj_data += msg->at(i).asString() + " ";
    }

    fromQString(obj_data.c_str());
    autoResize();

    update();
}

void* UILink::pdObject()
{
    return 0;
}
}
