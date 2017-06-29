// (c) 2017 Alex Nadzharov
// License: GPL3

#include "UIDSP.h"

#include <pdServer.hpp>

#include "CanvasView.h"

namespace qtpd {

void UIDSP::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{

    if (getEditMode() == em_Unlocked)
        emit selectBox(this, ev);

    dragOffset = ev->pos().toPoint();

    if (getEditMode() != em_Unlocked) {

        _value = !_value;
        //cmp_switch_dsp(_value);

        // TODO
        //parentCanvasView()->canvasData()->serverCanvas()->parentInstance()->dspOn();

        update();
    }
}
}