// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_FILEPARSER_H
#define CM_FILEPARSER_H

#include <QFile>
#include <QTextStream>

#include "PatchWindow.h"

namespace qtpd {
////
/// \brief Parses pd files on 'client' (GUI) side
///
class FileParser {
private:
    FileParser(){};

public:
    // or t_canvas?
    static PatchWindow* pdParserPrevWindow;
    static PatchWindow* pdParserWindow;
    static PatchWindow* pdParserFirstWindow;
    static std::string pdParserFileName;

    ////
    /// \brief [3.2] process legacy pd files
    /// \param list
    ///
    static bool legacyProcess(Canvas* cmcanvas, QStringList list);

    ////
    /// \brief [3.1] subroutine - formats list and send it to canvas as a string
    /// \param cmcanvas
    /// \param list
    /// \returns uiobject - that may be needed by legacyProcess to add more properties after object is created
    ///
    static UIObject* sendStringToCanvas(Canvas* cmcanvas, QStringList list);

    ////
    /// \brief [3] parses QStringLists of atoms to canvas - creates objects etc
    /// \details converts list, passes data to 'sendStringToCanvas'
    /// \param cmcanvas
    /// \param list
    ///
    static void parseStringListAtoms(Canvas* cmcanvas, QStringList list);

    ////
    /// \brief [2] checks first atoms ("#N", "#X" etc) and sends QStringList of contents to canvas
    /// \param line
    ///
    static void parseQStringList(QStringList atoms);

    ////
    /// \brief [1] opens file, converts to QStrings, calls 'parseString'
    /// \param fname
    ///
    static void open(QString fname);
};
}

#endif // CM_FILEPARSER_H
