#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "replicas/unit.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::add_replica(Replicas::Unit *r) {
  auto w = new QLabel(ui->replicas);

  connect(this, &MainWindow::refreshed, this, [=] {
    w->setText(r->name() + " " + r->path() + " " +
               QString::number(r->is_ready()));
  });

  qobject_cast<QBoxLayout *>(ui->replicas->layout())->insertWidget(0, w);
  emit refreshed();
}
