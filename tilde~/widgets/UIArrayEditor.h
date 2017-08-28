// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef UIARRAYEDITOR_H
#define UIARRAYEDITOR_H

#include <QObject>
#include <QPainter>
#include <QWidget>

#include "math.h"

// #include <pdServer.hpp>
#include "xpd-transition/xpd-headers.h"

// XPD-TODO
class ServerArray;

namespace tilde {
////
/// \brief Array Editor QWidget
class UIArrayEditor : public QWidget {
    Q_OBJECT
private:

    // XPD-TODO
    /*
    ServerArrayData* _arrayData;

    ArrayId _serverArray;
    */

public:
    explicit UIArrayEditor(QWidget* parent = 0);

    void paintEvent(QPaintEvent*);

    void setServerArray(ServerArray* arr);

signals:

public slots:
};
}

#endif // UIARRAYEDITOR_H