#ifndef REPLICAS_CONTROLLER_H
#define REPLICAS_CONTROLLER_H

#include <QList>
#include <QObject>

namespace Replicas {
class Unit;
}

class ReplicasController : public QObject {
  Q_OBJECT
public:
  explicit ReplicasController(QObject *parent = nullptr);

  void add_replica(Replicas::Unit *r);

public slots:
  void refresh();

signals:
  void refreshed();

private:
  QList<Replicas::Unit *> replicas_;
};

#endif // REPLICAS_CONTROLLER_H
