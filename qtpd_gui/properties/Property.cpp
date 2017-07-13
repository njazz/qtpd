// (c) 2017 Alex Nadzharov
// License: GPL3

#include "Property.h"

#include <QDebug>

using namespace std;

namespace qtpd {

void Property::setDefaultType(UIPropertyType type)
{
    if (_defaultData == QVariant())
        _type = type;
}

template <>
void Property::set(bool value)
{

    _data = (value);

    setDefaultType(ptBool);

    emit changed();
}

template <>
void Property::set(QPoint point)
{
    _data = QString::number(point.x()) + " " + QString::number(point.y());
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QPointF point)
{

    _data = QString::number(point.x()) + " " + QString::number(point.y());
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QRect rect)
{

    _data = (rect);
    setDefaultType(ptVector);

    emit changed();
}
template <>
void Property::set(QSize size)
{

    _data = QString::number(size.width()) + " " + QString::number(size.height());
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QSizeF size)
{
    _data = QString::number(size.width()) + " " + QString::number(size.height());
    setDefaultType(ptVec2);

    emit changed();
}

template <>
void Property::set(QColor color)
{
    QStringList sL;

    sL.append(QString::number(color.red()));
    sL.append(QString::number(color.green()));
    sL.append(QString::number(color.blue()));
    sL.append(QString::number(color.alpha()));

    _data = (sL);
    setDefaultType(ptColor);

    //qDebug() << "set" << sL;

    emit changed();
}

template <>
void Property::set(float val)
{
    _data = (val);
    setDefaultType(ptFloat);

    emit changed();
}

template <>
void Property::set(double val)
{

    _data = (val);
    setDefaultType(ptFloat);

    emit changed();
}

template <>
void Property::set(string string)
{
    _data = (QString(string.c_str()));

    setDefaultType(ptString);

    emit changed();
}

template <>
void Property::set(int val)
{

    _data = (val);
    setDefaultType(ptInt);

    emit changed();
}

template <>
void Property::set(QStringList strlist)
{

    _data = strlist;

    setDefaultType(ptStringList);

    emit changed();
}

template <>
void Property::set(QString string)
{
    _data = (string);
    setDefaultType(ptString);

    emit changed();
}

template <>
void Property::set(char const* string)
{
    _data = QString(string);
    setDefaultType(ptString);

    emit changed();
}

// -------------------------

Property::Property()
{
    _type = ptList; //?
    _applyToPd = false;
};

Property::Property(const Property& rval)
{
    Property* src = const_cast<Property*>(&rval);

    setGroup(src->group());
    setVersion(src->version());
    setType(src->type());

    setRawData(src->data());
    setRawDefaultData(src->defaultData());
}

Property::Property(Property& src)
{
    //Property* src = const_cast<Property*>(&rval);

    setGroup(src.group());
    setVersion(src.version());
    setType(src.type());

    setRawData(src.data());
    setRawDefaultData(src.defaultData());
}

const Property Property::operator=(const Property& rval)
{
    Property ret(rval);
    //qDebug() << "const" << ret.asQString();
    return ret;
}

Property Property::operator=(Property& rval)
{
    Property ret(rval);
    qDebug() << "non const" << ret.asQString();
    return Property(rval);
}

void Property::copyDataToDefault()
{
    _defaultData = _data;
}

void Property::setVersion(QString version)
{
    _version = version;
}

void Property::setGroup(QString grp)
{
    _group = grp;
}

void Property::setType(UIPropertyType type)
{
    _type = type;
}

void Property::setRawData(QVariant data)
{
    _data = data;
}

void Property::setRawDefaultData(QVariant data)
{
    _defaultData = data;
}

QString Property::version() { return _version; }
QString Property::group() { return _group; }

//////////

UIPropertyType Property::type() { return _type; };

QVariant Property::data()
{
    return _data;
}

QVariant Property::defaultData()
{
    return _defaultData;
}

// -------

QSize Property::asQSize()
{
    if (_data.toString().split(" ").size() < 2)
        return QSize(20, 20);

    QStringList sL = _data.toString().split(" ");

    return QSize(QString(sL.at(0)).toInt(), QString(sL.at(1)).toInt());
}

QPoint Property::asQPoint()
{
    if (_data.toString().split(" ").size() < 2)
        return QPoint(0, 0);

    QStringList sL = _data.toString().split(" ");

    return QPoint(QString(sL.at(0)).toInt(), QString(sL.at(1)).toInt());
}

QSizeF Property::asQSizeF()
{
    if (_data.toString().split(" ").size() < 2)
        return QSizeF(20, 20);

    QStringList sL = _data.toString().split(" ");

    return QSizeF(QString(sL.at(0)).toFloat(), QString(sL.at(1)).toFloat());
}

QPointF Property::asQPointF()
{
    if (_data.toString().split(" ").size() < 2)
        return QPointF(0, 0);

    QStringList sL = _data.toString().split(" ");

    return QPointF(QString(sL.at(0)).toFloat(), QString(sL.at(1)).toFloat());
}

float Property::asFloat()
{
    return _data.toFloat();
}

int Property::asInt()
{
    return _data.toInt();
}

bool Property::asBool()
{

    QStringList sL = _data.toString().split(" ");

    return sL.at(0).toInt() > 0;
}

float Property::asFontSize()
{
    return (_data.toFloat() < 8) ? 8 : _data.toFloat();
}

QColor Property::asQColor()
{
    QColor defaultColor = QColor(128, 128, 128, 255); //default gray

    QStringList sL = _data.toStringList();

    if (sL.size() < 4)
        return defaultColor;

    //qDebug() << "get" << sL;

    QColor ret = QColor(QString(sL.at(0)).toInt(), QString(sL.at(1)).toInt(), QString(sL.at(2)).toInt(), QString(sL.at(3)).toInt());

    //qDebug() << "color" << ret;

    return ret;
}

QStringList Property::asQStringList()
{
    return _data.toStringList();
}

string Property::asStdString()
{
    return _data.toString().toStdString();
}

QString Property::asPdSaveString()
{
    // if (!_type == ptString)
    QString ret = _data.toStringList().join(" ");
    // else
    //     QString ret = _data.toStringList().join("\ ");

    ret = escapeString(ret);
    return ret;
}

QString Property::asQString()
{

    return _data.toStringList().join(" ");
}

// ----------

QString Property::escapeString(QString input)
{
    // todo regexp

    QString ret;

    ret = input.split(" ").join("\\ ");
    ret = ret.split("\n").join("\\n");
    ret = ret.split("\r").join("");
    ret = ret.split(",").join("\\,");
    ret = ret.split(".").join("\\.");
    ret = ret.split("@").join("\\@");
    ret = ret.split(";").join("\\;");
    return ret;
}

QString Property::unescapeString(QString input)
{
    // todo regexp

    QString ret;

    ret = input.split("\\ ").join(" ");
    ret = ret.split("\\n").join("\n");
    ret = ret.split("\\,").join(",");
    ret = ret.split("\\.").join(".");
    ret = ret.split("\\@").join("@");
    ret = ret.split("\\;").join(";");
    return ret;
}
}
