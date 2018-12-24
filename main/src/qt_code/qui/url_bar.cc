#include "url_bar.h"

#include "src/cef_code/core.h"
#include <iostream>
using namespace std;

namespace qui {

UrlBar::UrlBar(QWidget* parent) : QLineEdit(parent) {
  setFocusPolicy(Qt::FocusPolicy::StrongFocus);
}

void UrlBar::returnPressed() {
  CefCore::cef_widget->setFocus();
}

} // namespace ui
