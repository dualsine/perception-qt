#include "src/cef_code/bindings_qt/widget.h"

CefWidget::CefWidget(QWidget *parent) : QWidget(parent), cef_core_(CefCore::Instance()) {
  this->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

CefWidget::~CefWidget() {
  if (browser_) {
    browser_->GetHost()->CloseBrowser(true);
  }
}

void CefWidget::moveEvent(QMoveEvent *event) {
  this->updateSize();
}

void CefWidget::resizeEvent(QResizeEvent *event) {
  this->updateSize();
}

void CefWidget::focusOut() {
  // unfocus active items on page
  CefString code("if ('activeElement' in document) document.activeElement.blur();");
  CefString code_url("");
  CefCore::browser->GetMainFrame()->ExecuteJavaScript(code, code_url, 0);
}
