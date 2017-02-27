#ifndef CM_WIDGET_H
#define CM_WIDGET_H

#include <QWidget>

// Widget extension
// check / fix

class cm_widget : public QWidget
{
    Q_OBJECT
public:
    explicit cm_widget(QWidget *parent = 0);

signals:

    void mousePressed(cm_widget* obj, QMouseEvent* ev);
    void mouseReleased(cm_widget* obj, QMouseEvent* ev);
    void mouseEntered();
    void mouseLeaved();

public slots:

    void s_MousePressed();
    void s_MouseReleased();
    void s_MouseEntered();
    void s_MouseLeaved();

    virtual void s_InMousePressed(cm_widget* obj, QMouseEvent* ev);
    virtual void s_InMouseReleased(cm_widget* obj, QMouseEvent* ev);
    virtual void s_InMouseEntered();
    virtual void s_InMouseLeaved();

    virtual void s_OutMousePressed(cm_widget* obj, QMouseEvent* ev);
    virtual void s_OutMouseReleased(cm_widget* obj, QMouseEvent* ev);
    virtual void s_OutMouseEntered();
    virtual void s_OutMouseLeaved();
};

#endif // CM_WIDGET_H
