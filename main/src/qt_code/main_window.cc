#include "ui_mainwindow.h"
#include "src/qt_code/main_window.h"
#include "src/qt_code/elements.h"
#include "src/qt_code/qui/url_bar.h"
#include "src/global_actions.h"
#include "src/cef_code/blink_signals.h"
#include "src/perception/signals_server.h"

#include "../signals/observer.h"
#include <thread>
#include <iostream>
using namespace std;

#include "src/perception/signals_server.h"
#include "src/perception/config.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  Perception::Config::bs = new Perception::BlinkSignals();
  Perception::Config::ss = new Perception::SignalsServer();

  if (startTimer(15) == 0) {
    throw std::runtime_error("Unable to start main timer");
  }

  keyboard = new Qt::Keyboard(this);

  CefCore::cef_widget = new CefWidget();

  Qt::Elements::url_bar = this->findChild<QLineEdit*>("urlBar");

  QGridLayout *browser_layout = this->findChild<QGridLayout*>("browserLayout");
  connect(Qt::Elements::url_bar, SIGNAL(returnPressed()), this, SLOT(urlBarNewAddressEntered()));

  browser_layout->addWidget(CefCore::cef_widget, 1, 0);
  browser_layout->setContentsMargins(0, 0, 0, 0);
  browser_layout->setSpacing(0);
  browser_layout->setRowStretch(0, 0);
  browser_layout->setRowStretch(1, 1);

  auto override_cef_widget = CefCore::cef_widget->embedBrowser(this);
  if (override_cef_widget) {
    browser_layout->addWidget(override_cef_widget, 1, 0);
  }

  Qt::Elements::btn_top_options = this->findChild<QPushButton*>("btnTopOptions");
  connect(Qt::Elements::btn_top_options, SIGNAL(clicked()), this, SLOT(showOptions()));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::timerEvent(QTimerEvent*) {
  CefCore::Instance()->tick();
  Perception::SignalsServer::tick();
}

void MainWindow::urlBarNewAddressEntered() {
  GlobalActions::openUrl(Qt::Elements::url_bar->text().toStdString());
}

void MainWindow::showOptions() {
  GlobalActions::switchOptionsPage();
}
