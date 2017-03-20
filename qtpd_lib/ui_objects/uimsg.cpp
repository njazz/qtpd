//
//  ui_msg.cpp
//
//
//  Created by Alex Nadzharov on 03/03/17.
//
//

#include "m_pd.h"

#include "pdlib.hpp"

#include "../ceammc-lib/ceammc_atomlist.h"
#include <stdlib.h>

using namespace ceammc;

static t_class* ui_msg_class;

typedef struct _ui_msg {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    t_symbol* s;

    AtomList* msg;

    t_outlet* out1;

} t_ui_msg;

// special
extern "C" void uimsg_set_updateUI(t_pd* x, void* obj, t_updateUI func)
{
    //weird fix, test that
    if (x)
    {
        ((t_ui_msg*)x)->updateUI = func;
        ((t_ui_msg*)x)->uiobj = obj;
    }
}

static void uimsg_set(t_ui_msg* x, t_symbol* s, int argc, t_atom* argv)
{
    //post("uimsg set");

    if (x->msg)
        delete x->msg;

    AtomList list = AtomList(argc, argv);

    if (list.size() == 0) {
        //one symbol or bang
        x->s = s;
        x->msg = new AtomList(0, 0);
    } else {
        if (list.at(0).isFloat()) {
            if (list.size() > 1) {
                x->s = &s_list;
                //list.remove(0);
                x->msg = new AtomList(list);
            } else {
                x->s = &s_float;
                x->msg = new AtomList(list);
            }
        } else {
            x->s = list.at(0).asSymbol();
            //list.remove(0);
            x->msg = new AtomList(list);
        }
    }

    //    if (list.size())
    //        if (list.at(0).isSymbol()) {
    //            x->s = list.at(0).asSymbol();
    //            if (list.size() > 1)
    //                list.remove(0);
    //        } else
    //            x->s = &s_list;

    //    x->msg = new AtomList(list);

    //    x->s = s;

    //quick fix
    //    if (x->msg->size())
    //        if (x->msg->at(0).asSymbol() == gensym("bang")) {
    //            *x->msg = AtomList(0, 0);
    //        }

    //move this later
    if (x->updateUI)
        x->updateUI(x->uiobj, *x->msg); //x->msg
}

static void uimsg_bang(t_ui_msg* x) // t_symbol *s, int argc, t_atom* argv
{
    if (x->msg->size())
        x->msg->output(x->out1);
    else
        outlet_bang(x->out1);
}

static void* uimsg_new(t_symbol* s, int argc, t_atom* argv)
{
    t_ui_msg* x = (t_ui_msg*)pd_new(ui_msg_class);

    x->s = s;

    x->msg = new AtomList(argc, argv);

    x->out1 = outlet_new((t_object*)x, &s_anything);

    return (void*)x;
}

void uimsg_save(t_gobj* z, t_binbuf* b)
{
    t_ui_msg* x = (t_ui_msg*)z;

    binbuf_addv(b, "ss", gensym("#X"), gensym("obj"));
    binbuf_addv(b, "ff", (float)x->x_obj.te_xpix, (float)x->x_obj.te_ypix);
    binbuf_addv(b, "s", gensym("ui.msg"));
    binbuf_add(b, x->msg->size(), x->msg->toPdData());
    binbuf_addv(b, ";");
}

static void uimsg_free(t_object* obj)
{
    t_ui_msg* x= (t_ui_msg*)obj;

    if (x->msg)
        delete x->msg;
    if (x->s)
        delete x->s;
}

//extern "C"
extern "C" void setup_ui0x2emsg()
{
    // printf("ui.msg init\n");
    // class_new()
    ui_msg_class = class_new(gensym("ui.msg"),
        (t_newmethod)(uimsg_new),
        (t_method)(0),
        sizeof(t_ui_msg), 0, A_GIMME, 0);

    class_addmethod(ui_msg_class, (t_method)uimsg_set, &s_anything, A_GIMME, 0);
    class_addmethod(ui_msg_class, (t_method)uimsg_bang, &s_bang, A_NULL, 0);

    class_setsavefn(ui_msg_class, uimsg_save);
}
