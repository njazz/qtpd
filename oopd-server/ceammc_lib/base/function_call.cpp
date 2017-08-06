/*****************************************************************************
 * Copyright 2017 Serge Poltavsky. All rights reserved.
 *
 * This file may be distributed under the terms of GNU Public License version
 * 3 (GPL v3) as defined by the Free Software Foundation (FSF). A copy of the
 * license should have been included with this file, or the project in which
 * this file belongs to. You may also find the details of GPL v3 at:
 * http://www.gnu.org/licenses/gpl-3.0.txt
 *
 * If you have any questions regarding the use of this file, feel free to
 * contact the author of this file, or the owner of the project in which
 * this file belongs to.
 *****************************************************************************/
#include "function_call.h"
#include "function.h"

#include "ceammc_factory.h"

FunctionCall::FunctionCall(const PdArgs& a)
    : BaseObject(a)
    , name_(0)
{
    createInlet(&name_);
    createOutlet();

    Atom name = positionalArgument(0, Atom());
    if (name.isSymbol())
        name_ = name.asSymbol();
}

void FunctionCall::onBang()
{
    Function* fn = getFunc();
    if (!fn)
        return;

    fn->onBang();
    outputResult(fn);
}

void FunctionCall::onFloat(float f)
{
    Function* fn = getFunc();
    if (!fn)
        return;

    fn->onFloat(f);
    outputResult(fn);
}

void FunctionCall::onList(const AtomList& lst)
{
    Function* fn = getFunc();
    if (!fn)
        return;

    fn->onList(lst);
    outputResult(fn);
}

void FunctionCall::onSymbol(t_symbol* s)
{
    Function* fn = getFunc();
    if (!fn)
        return;

    fn->onSymbol(s);
    outputResult(fn);
}

Function* FunctionCall::getFunc()
{
    Function* fn = Function::function(name_);
    if (!fn) {
        OBJ_ERR << "invalid function call: " << (name_ ? name_->s_name : "");
    }

    return fn;
}

void FunctionCall::outputResult(Function* fn)
{
    Message msg(fn->result());

    if (!msg.isNone())
        messageTo(0, msg);
}

extern "C" void function_call_setup()
{
    ObjectFactory<FunctionCall> f("function.call");
    f.addAlias("func.call");
}
