
#include <QTimer>

#include "replicas/unit.h"

#include "replicas_controller.h"

ReplicasController::ReplicasController(QObject *parent) : QObject{parent} {

  auto t = new QTimer(this);
  connect(t, &QTimer::timeout, this, &ReplicasController::refresh);
  t->start(3000);
}

void ReplicasController::add_replica(Replicas::Unit *r) {
  r->setParent(this);
  replicas_.push_back(r);
  connect(r, &QObject::destroyed, this, [&](QObject *o) {
    replicas_.removeAll(qobject_cast<Replicas::Unit *>(o));
  });
}

void ReplicasController::refresh() { emit refreshed(); }
