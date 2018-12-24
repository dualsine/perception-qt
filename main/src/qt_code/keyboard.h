#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QMainWindow>
#include "src/global_actions.h"

namespace Qt {

class Keyboard : public QWidget
{
Q_OBJECT
public:
  Keyboard(QMainWindow* main_window);

  void initShortcut(QKeySequence keys, const char *func);
private:
  QMainWindow* main_window_;
private slots:
  void ESC();
  void SHIFT_D();
  void CTRL_L();
};

} // namespace Qt

#endif // KEYBOARD_H
