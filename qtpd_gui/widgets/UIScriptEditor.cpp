#include "UIScriptEditor.h"

#include <QPushButton>

namespace qtpd {
UIScriptEditor::UIScriptEditor(QWidget* parent)
    : QWidget(parent)
{

    QFont font = QFont(PREF_QSTRING("Font"), 11, 0, false);

    _editor = new UIScriptTextEdit();
    _editor->setFont(font);
    _editor->setAttribute(Qt::WA_MacShowFocusRect, 0);
    _editor->setCursorWidth(2);
    _editor->setParent(this);

    setBaseSize(300, 200);

    QPalette Pal; //palette());
    Pal.setColor(QPalette::Background, QColor(224, 240, 255));
    Pal.setColor(QPalette::Base, QColor(240, 248, 255));
    _editor->setPalette(Pal);

    //buttons
    QPushButton* b1 = new QPushButton("Run");
    b1->setParent(this);
    b1->setFont(font);
    b1->move(40, 1);
    b1->setFixedSize(40, 20);
    b1->show();
    connect(b1, &QPushButton::clicked, this, &UIScriptEditor::btnRun);

    b1 = new QPushButton("Load");
    b1->setParent(this);
    b1->setFont(font);
    b1->setFixedSize(50, 20);
    b1->move(100, 1);
    b1->show();
    connect(b1, &QPushButton::clicked, this, &UIScriptEditor::btnLoad);

    b1 = new QPushButton("Save");
    b1->setParent(this);
    b1->setFont(font);
    b1->move(150, 1);
    b1->setFixedSize(50, 20);
    b1->show();
    connect(b1, &QPushButton::clicked, this, &UIScriptEditor::btnSave);

    b1 = new QPushButton("Clear");
    b1->setParent(this);
    b1->setFont(font);
    b1->move(220, 1);
    b1->setFixedSize(50, 20);
    b1->show();
    connect(b1, &QPushButton::clicked, this, &UIScriptEditor::btnClear);
}
}
