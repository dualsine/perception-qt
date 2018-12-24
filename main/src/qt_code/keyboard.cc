// This is part of keyboard shortcuts handled in Qt side. For Cef please look into src/Browser/cef_client_handler.cc
//

#include "src/qt_code/keyboard.h"
#include <QShortcut>

namespace Qt {

Keyboard::Keyboard(QMainWindow* main_window) : main_window_(main_window) {
  initShortcut(QKeySequence(Qt::Key_Escape), SLOT(ESC()));
  initShortcut(QKeySequence(Qt::SHIFT + Qt::Key_D), SLOT(SHIFT_D()));
  initShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), SLOT(CTRL_L()));
}

void Keyboard::initShortcut(QKeySequence keys, const char *func) {
  QShortcut* shortcut = new QShortcut(keys, main_window_);
  shortcut->setContext(Qt::ApplicationShortcut);
  connect(shortcut, SIGNAL(activated()), this, func);
}

void Keyboard::ESC() {
  GlobalActions::closeApp();
}

void Keyboard::SHIFT_D() {
  GlobalActions::openDevTools();
}

void Keyboard::CTRL_L() {
  GlobalActions::focusUrlBar();
}

} // namespace Qt
