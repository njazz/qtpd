// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef PY_QTPD_H
#define PY_QTPD_H

#include <QObject>
#include <QString>
#include <QStringList>

#include <PythonQt.h>

#include "cm_patchwindow.h"

#include "cm_preferences.h"

#include "cm_filesaver.h"

using namespace qtpd;

///////////////////////////////////////////////////////////////////////////////////////////////////////

class pyUIObjectDecorator : public QObject {
    Q_OBJECT

public Q_SLOTS:

    void addInlet(UIObject* obj)
    {
        if (obj)
            obj->addInlet();
    }

    void addOutlet(UIObject* obj)
    {
        if (obj)
            obj->addOutlet();
    }

    void pdMessage(UIObject* obj, QString data)
    {
        if (obj->pdObject()) {
            cmp_sendstring((t_pd*)obj->pdObject(), data.toStdString());
        }
    }

    // test
    void scale(UIObject* obj, float scale)
    {
        obj->setScale(scale);
    }

    ///////

    PropertyList* prop(UIObject* obj)
    {
        return (PropertyList*)obj->properties();
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class pyPatchWindowDecorator : public QObject {
    Q_OBJECT

public Q_SLOTS:

    Canvas* canvas(PatchWindow* w)
    {
        return w->canvas;
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class pyCanvasDecorator : public QObject {
    Q_OBJECT

public Q_SLOTS:

    UIObject* createObject(Canvas* c, QString obj_name, QString obj_data, int x, int y)
    {
        return c->Canvas::createObject(obj_name.toStdString(), obj_data.toStdString(), QPoint(x, y));
    }

    //todo templates
    void moveObject(Canvas* o, int x, int y)
    {
        o->move(x, y);
    }

    void moveObject(UIObject* o, int x, int y)
    {
        o->move(x, y);
    }

    void resizeObject(UIObject* o, int w, int h)
    {
        o->setFixedSize(w, h);
    }

    //////////
    // edit

    void selectObject(Canvas* c, UIObject* obj)
    {
        c->selectBox(obj);
    }

    void selectAll(Canvas* c)
    {
        c->selectAll();
    }

    void deselectAll(Canvas* c)
    {
        c->deselectBoxes();
    }

    void deleteObjectInCanvas(Canvas* c, UIObject* obj)
    {
        c->deleteBox(obj);
    }

    void patchcord(Canvas* c, UIObject* obj1, int out1, UIObject* obj2, int in2)
    {
        c->patchcord(obj1, out1, obj2, in2);
    }

    //////////
    // objects

    // TODO
    objectVec objects(Canvas* c)
    {
        return c->objectBoxes();
    }

    objectVec selectedObjects(Canvas* c)
    {
        return c->selectedObjectBoxes();
    }

    //////////
    // patchcords

    patchcordVec patchcords(Canvas* c)
    {
        return c->patchcords();
    }

    patchcordVec selectedPatchcords(Canvas* c)
    {
        return c->selectedPatchcords();
    }

    patchcordVec patchcordsFor(Canvas* c, UIObject* obj)
    {
        return c->patchcordsForObject(obj);
    }

    void deletePatchcordsFor(Canvas* c, UIObject* obj)
    {
        c->deletePatchcordsFor(obj);
    }

    //////////
    // file

    QStringList pdPatch(Canvas* c)
    {
        return c->canvasAsPdStrings();
    }


    // test
    void scale(Canvas* c, float scale)
    {
        c->setScale(scale);
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class pyPropertyListDecorator : public QObject {
    Q_OBJECT

public Q_SLOTS:
    QString get(PropertyList* p, QString name)
    {
        return p->PropertyList::get(name.toStdString())->asQString();
    }

    void set(PropertyList* p, QString name, QString data)
    {
        p->PropertyList::set(name.toStdString(), data);
    }

    QStringList names(PropertyList* p)
    {
        return p->PropertyList::names();
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////

class pyQtpd : public QObject {
    Q_OBJECT

public:
    explicit pyQtpd(QObject* parent = 0){};

public Q_SLOTS:
    PyObject* getMainModule()
    {
        return PythonQt::self()->getMainModule();
    }

    //todo separate classes / decorators

    PatchWindow* newPatchWindow()
    {
        PatchWindow* ret;
        ret = PatchWindow::newWindow();
        ret->show();
        return ret;
    };

    //////////
    // pdLib

    void startDsp()
    {
        cmp_switch_dsp(true);
    }

    void stopDsp()
    {
        cmp_switch_dsp(false);
    }

    void post(QString msg)
    {
        cmp_post(msg.toStdString());
    }

    QStringList externals()
    {
        AtomList list = cmp_get_loaded_list();
        QStringList ret;

        for (int i=0;i<list.size();i++)
        {
            ret += list.at(i).asString().c_str();
        }

        return ret;
    }

    void loadLib(QString lib)
    {
        cmp_loadlib(lib.toStdString());
    }

    //////////
    // app preferences

    PropertyList* pref()
    {
        return (PropertyList*)&Preferences::inst();
    }
};

#endif // PY_QTPD_H
