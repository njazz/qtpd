//
//  oopdinstance.cpp
//
//
//  Created by Alex Nadzharov on 24/03/17.
//
//

#include "m_pd.h"

#include "pdlib.hpp"

#include "../ceammc-lib/ceammc_atomlist.h"
#include <stdlib.h>

using namespace ceammc;

static t_class* oopdinstance_class;

typedef struct _oopdinstance {
    t_object x_obj;

    t_updateUI updateUI;
    void* uiobj;

    t_outlet* out1;

} t_oopdinstance;

// special
//extern "C" void oopdinstance_set_updateUI(t_pd* x, void* obj, t_updateUI func)
//{
//    //weird fix, test that
//    if (x) {
//        ((t_oopdinstance*)x)->updateUI = func;
//        ((t_oopdinstance*)x)->uiobj = obj;
//    }
//}

static void oopdinstance_anything(t_oopdinstance* x, t_symbol* s, int argc, t_atom* argv)
{
    if (s == gensym("__output")) {
        AtomList l = AtomList(argc, argv);
        l.output(x->out1);
    } else {

        if (x->updateUI)
            x->updateUI (x->uiobj, AtomList(argc, argv));

    }
}

static void* oopdinstance_new(t_symbol* s, int argc, t_atom* argv)
{
    t_oopdinstance* x = (t_oopdinstance*)pd_new(oopdinstance_class);

    x->out1 = outlet_new((t_object*)x, &s_anything);

    return (void*)x;
}

static void oopdinstance_free(t_object* obj)
{
    // stub. free method is possibly useless here
    t_oopdinstance* x = (t_oopdinstance*)obj;
}

//extern "C"
extern "C" void setup_pdinstance()
{
    oopdinstance_class = class_new(gensym("pdinstance"),
        (t_newmethod)(oopdinstance_new),
        (t_method)(0),
        sizeof(t_oopdinstance), 0, A_GIMME, 0);

    class_addmethod(oopdinstance_class, (t_method)oopdinstance_anything, &s_anything, A_GIMME, 0);
}