//
//  ui_sliders.cpp
//
//
//  Created by Alex Nadzharov on 13/03/17.
//
//

#include "m_pd.h"

#include "pdlib.hpp"

#include "../ceammc-lib/ceammc_atomlist.h"
#include <stdlib.h>

using namespace ceammc;

static t_class* ui_sliders_class;

typedef struct _ui_sliders {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    float val;

    t_outlet* out1;

} t_ui_sliders;

// special
extern "C" void uisliders_set_updateUI(t_pd* x, void* obj, t_updateUI func)
{
    ((t_ui_sliders*)x)->updateUI = func;
    ((t_ui_sliders*)x)->uiobj = obj;
}

///////

static void uisliders_set(t_ui_sliders* x, t_symbol* s, int argc, t_atom* argv)
{
    if (argc)
        x->val = AtomList(argc, argv).at(0).asFloat();

    AtomList msg = AtomList(Atom(x->val));

    if (x->updateUI)
        x->updateUI(x->uiobj, msg);
}

static void uisliders_bang(t_ui_sliders* x)
{
    AtomList(Atom(x->val)).output(x->out1);
}

static void uisliders_float(t_ui_sliders* x, t_float f)
{
    x->val = f;

    AtomList msg = AtomList(Atom(x->val));

    msg.output(x->out1);

    if (x->updateUI)
        x->updateUI(x->uiobj, msg);
}

///////

static void* uisliders_new(t_symbol* s, int argc, t_atom* argv)
{
    t_ui_sliders* x = (t_ui_sliders*)pd_new(ui_sliders_class);

    x->val = 0;
    x->uiobj = 0;

    x->out1 = outlet_new((t_object*)x, &s_anything);

    return (void*)x;
}

static void uisliders_free(t_object* obj)
{
}

//extern "C"
extern "C" void setup_ui0x2esliders()
{
    ui_sliders_class = class_new(gensym("ui.sliders"),
        (t_newmethod)(uisliders_new),
        (t_method)(0),
        sizeof(t_ui_sliders), 0, A_GIMME, 0);

    class_addmethod(ui_sliders_class, (t_method)uisliders_set, &s_anything, A_GIMME, 0);
    class_addmethod(ui_sliders_class, (t_method)uisliders_bang, &s_bang, A_NULL, 0);

    class_addfloat(ui_sliders_class, (t_method)uisliders_float);
}
