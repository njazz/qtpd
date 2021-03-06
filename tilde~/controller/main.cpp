// (c) 2017 Alex Nadzharov
// License: GPL3

#include <QApplication>

#include "PatchWindow.h"
#include "PdWindow.h"

//#include "BaseMenu.h"

#include "ObjectLoader.h"

#include "AudioSettings.h"
#include "Preferences.h"

#include "ApplicationController.h"

#include <assert.h>

// python
#ifdef WITH_PYTHON
#include "python/PythonQtScriptingConsole.h"
#include "python/wrappers/py_wrappers.h"
#include <PythonQt.h>
#include <PythonQt_QtAll.h>
#endif

using namespace tilde;

int main(int argc, char* argv[])
{

    QApplication a(argc, argv);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

#ifndef _WIN32
    a.setQuitOnLastWindowClosed(false);
#endif

    a.setCursorFlashTime(500);

    new ApplicationController();
    return a.exec();
}
