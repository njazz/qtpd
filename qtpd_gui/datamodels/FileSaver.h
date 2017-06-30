// (c) 2017 Alex Nadzharov
// License: GPL3

#ifndef CM_FILESAVER_H
#define CM_FILESAVER_H

//
class QString;
class QFile;

namespace qtpd {

class PatchWindow;

class CanvasData;

////
/// \brief saves pd files on 'client' (GUI) side
///
class FileSaver {
private:
    FileSaver(){};

public:

    ////
    /// \brief save file to disk; runs 'savecanvas' recursively
    /// \param fname
    /// \param canvas
    ///
    static void save(QString fname, CanvasData* canvasData);

    ////
    /// \brief new API saveCanvas
    /// \param canvas
    /// \param file
    ///
    static void saveCanvas(CanvasData* CanvasData, QFile* file);



};
}

#endif // CM_FILESAVER_H
