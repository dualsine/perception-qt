#pragma once
#ifndef QT_CEF_POC_MAINWINDOW_H_
#define QT_CEF_POC_MAINWINDOW_H_

#include <QtWidgets>
#include "src/cef_code/core.h"
#include "src/cef_code/bindings_qt/widget.h"
#include "src/qt_code/keyboard.h"

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  Qt::Keyboard* keyboard;
  QPointer<QWindow> top_window;
  QPointer<QWidget> top_window_widget;

  MainWindow(QWidget *parent = 0);
  ~MainWindow();
public slots:
  void urlBarNewAddressEntered();

protected:
  void timerEvent(QTimerEvent *event);

private:
  Ui::MainWindow *ui;

private slots:
  void showOptions();
};

#endif // QT_CEF_POC_MAINWINDOW_H_
