#ifndef CM_PATCHWINDOW_H
#define CM_PATCHWINDOW_H

#include "BaseWindow.h"

namespace tilde {

class CanvasView;
class UIBox;
class PatchWindowController;

////
/// \brief Patch window. Creates scroll view and cm_canvas; Creates menu commands, forwards them to cm_canvas
class PatchWindow : public BaseWindow {

private:
    PatchWindowController* _controller;

    QScrollArea* _scroll;

    ////

    QAction* _selectAllAct;
    QAction* _selectAgainAct;

    QAction* _delObjectAct;
    QAction* _editModeAct;

    QAction* _putObjectAct;
    QAction* _putMessageAct;

    //    QAction *putSymbolAct;
    QAction* putCommentAct;

    QAction* putBangAct;
    QAction* putToggleAct;
    QAction* putNumberAct;
    QAction* putSliderAct;
    QAction* putKnobAct;
    QAction* putRadioAct;
    QAction* putDisplay;

    QAction* putArray;

    QAction* putKeyboard;
    QAction* putSlider2D;
    QAction* putBPF;

    QAction* putRangeSliderAct;
    QAction* putSlidersAct;
    QAction* putIncDecAct;
    QAction* putMatrixAct;

    QAction* putScope;
    QAction* putSpectroscope;

    QAction* putScriptAct;

    QAction* putPdClass;
    QAction* putPdInstance;

    QAction* showGridAct;
    QAction* snapToGridAct;

    QAction* alignToGridAct;

    QAction* alignLeftAct;
    QAction* alignCenterAct;
    QAction* alignRightAct;
    QAction* alignTopAct;
    QAction* alignBottomAct;

    QAction* distHAct;
    QAction* distVAct;

    QAction* tidyUpAct;

    QAction* groupObjAct;
    QAction* ungroupObjAct;

    QAction* zoomInAct;
    QAction* zoomOutAct;

    QAction* zoom100Act;

    CanvasView* _canvasView;

private slots:

    void slotEnableUndo(bool v);
    void slotEnableRedo(bool v);

    void slotResize(int);
    void slotMove(int);

public:
    PatchWindow();

    CanvasView* canvasView() { return _canvasView; };
    void setCanvasView(CanvasView* v) { _canvasView = v; }

    void setController(PatchWindowController* c);
    PatchWindowController* controller() { return _controller; } //temporary!

    void createActions();
    void createMenus();

    // ----------
    void moveEvent(QMoveEvent *);
    void resizeEvent(QResizeEvent* );

    //----------------------------------------------------------------------------------------

    // todo less spaghetti

    void newObjectBox();
    void newMessageBox();
    void newFloatBox();
    void newCommentBox();
    void newBangBox();
    void newToggleBox();
    void newScriptBox();
    void newArrayBox();
    void newSliderBox();
    void newRadioBox();
    void newPdClassBox();
    void newPdInstanceBox();

    // ----------------------------------------------------

    void objectMakerDone();

    void setEditMode();
    void setGridVisible();
    void setGridSnap();

    // -------

    void closeEvent(QCloseEvent* event);

    // -------

    void setFileName(QString fname);

    ////
    /// \brief keys: ctrl for temporary lock; esc to stop editing actions
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);

    //
    void zoomIn();
    void zoomOut();

    void zoom100();
};
}

#endif // CM_PATCHWINDOW_H
