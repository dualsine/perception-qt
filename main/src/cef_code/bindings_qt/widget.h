#pragma once
#ifndef QT_CEF_POC_CEFWIDGET_H_
#define QT_CEF_POC_CEFWIDGET_H_

#include "cef/include/cef_app.h"
#include "cef/include/cef_browser.h"
#include "src/cef_code/core.h"
#include "src/qt_code/main_window.h"

class CefCore;
class MainWindow;

class CefWidget : public QWidget {
  Q_OBJECT
public:
  CefWidget(QWidget *parent = 0);
  ~CefWidget() override;

  // If result is non-null, it needs to replace this widget
  QPointer<QWidget> embedBrowser(MainWindow *main_window);
  void updateSize();
  void focusOut();

  QPointer<QWindow> window;
  QPointer<QWidget> embedded_widget;

protected:
  void moveEvent(QMoveEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

private:
  CefCore* cef_core_;
  CefRefPtr<CefBrowser> browser_;
};

class CefEmbedWindow : public QWindow {
 Q_OBJECT
public:
  CefEmbedWindow(QPointer<CefWidget> cef_widget, QWindow *parent = 0)
    : QWindow(parent), cef_widget_(cef_widget) {}
protected:
  void moveEvent(QMoveEvent *) {
    if (cef_widget_) cef_widget_->updateSize();
  }
  void resizeEvent(QResizeEvent *) {
    if (cef_widget_) cef_widget_->updateSize();
  }
private:
  QPointer<CefWidget> cef_widget_;
};

#endif // QT_CEF_POC_CEFWIDGET_H_
