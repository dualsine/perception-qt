#ifndef URL_BAR_H
#define URL_BAR_H

#include <QLineEdit>
#include <QWidget>

namespace qui {

class UrlBar : public QLineEdit {
Q_OBJECT
public:
  UrlBar(QWidget *parent = nullptr);

  void returnPressed();
};

} // namespace ui

#endif // URL_BAR_H
