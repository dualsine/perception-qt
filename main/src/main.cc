#include <QApplication>
#include "src/qt_code/main_window.h"
#include "src/cef_code/core.h"

int main(int argc, char *argv[]) {
  CefCore cef_core(argc, argv);

  QApplication qt_app(argc, argv);

  MainWindow win;
  win.show();
  win.activateWindow();
  win.raise();

  int qt_exit_code = qt_app.exec(); // .exec() blocks execution
  // add signals handle
  return 0;
}
