#ifndef QT_CODE_ELEMENTS_H
#define QT_CODE_ELEMENTS_H

#include <QApplication>
#include <QPointer>
#include <QLineEdit>
#include <QPushButton>
#include "main_window.h"

namespace Qt{

class Elements : public QObject {
Q_OBJECT
public:
  static QPointer<QLineEdit> url_bar;
  static QPointer<QPushButton> btn_top_options;
  static QPointer<MainWindow> main_window;
};

} // namespace Qt

#endif // ELEMENTS_H
