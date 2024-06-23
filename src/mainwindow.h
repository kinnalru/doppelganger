#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Replicas {
class Unit;
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void add_replica(Replicas::Unit *r);

signals:
  void refreshed();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
