// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"

#include <QDebug>

namespace qtpd {

template <>
void Property::set(AtomList list)
{
    _data = list;
    _type = ptList;
}

template <>
void Property::set(QPoint point)
{
    AtomList list;

    list.append(point.x());
    list.append(point.y());

    _data = list;
    _type = ptVector;

    emit changed();
}

template <>
void Property::set(bool value)
{
    AtomList list;

    list.append(int(value));

    _data = list;
    _type = ptBool;

    emit changed();
}

template <>
void Property::set(QPointF point)
{
    AtomList list;

    list.append(point.toPoint().x());
    list.append(point.toPoint().y());

    _data = list;
    _type = ptVector;

    emit changed();
}

template <>
void Property::set(QRect rect)
{
    AtomList list;

    list.append(rect.top());
    list.append(rect.left());
    list.append(rect.width());
    list.append(rect.height());

    _data = list;
    _type = ptVector;

    emit changed();
}
template <>
void Property::set(QSize size)
{
    AtomList list;

    list.append(size.width());
    list.append(size.height());

    _data = list;
    _type = ptVector;

    emit changed();
}

template <>
void Property::set(QSizeF size)
{
    AtomList list;

    list.append(size.toSize().width());
    list.append(size.toSize().height());

    _data = list;
    _type = ptVector;

    emit changed();
}

template <>
void Property::set(QColor color)
{
    AtomList list;

    list.append(color.red());
    list.append(color.green());
    list.append(color.blue());
    list.append(color.alpha());

    _data = list;
    _type = ptColor;

    emit changed();
}

template <>
void Property::set(float val)
{
    _data = AtomList(val);
    _type = ptFloat;

    emit changed();
}

template <>
void Property::set(double val)
{
    _data = AtomList(val);
    _type = ptFloat;

    emit changed();
}

template <>
void Property::set(t_symbol* s)
{
    _data = AtomList(s);
    _type = ptSymbol;

    emit changed();
}

template <>
void Property::set(std::string string)
{
    _data = AtomList(gensym(string.c_str()));
    _type = ptList;

    emit changed();
}

template <>
void Property::set(int val)
{
    _data = AtomList(val);
    _type = ptInt;

    emit changed();
}

template <>
void Property::set(QStringList strlist)
{
    QStringList::iterator it;
    AtomList* list = new AtomList();

    for (it = strlist.begin(); it != strlist.end(); ++it) {
        QString str = *it;
        //qDebug() << "str" << str;
        if (str != "") {
            //check if it is not float
            if (str.toFloat() != 0)
                list->append(Atom(str.toFloat()));
            else

                list->append(Atom(gensym(str.toStdString().c_str())));
        } else {
            //fix missing spaces
            list->append(Atom(gensym("")));
        }
    }

    //qDebug() << "data size" << list->size();

    //check, different type for text files
    _type = ptStringList;
    _data = (*list);

    emit changed();
}

//template <>
void Property::set(QString string)
{
    //    data_ = AtomList(gensym(string.toStdString().c_str()));
    //    type_ = ptString;
    Property::set(string.split(" "));

    emit changed();
}
}
