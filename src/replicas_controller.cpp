
#include <QTimer>

#include "unison.h"

#include "replicas_controller.h"

ReplicasController::ReplicasController(QObject *parent) : QObject{parent} {

  auto t = new QTimer(this);
  connect(t, &QTimer::timeout, this, &ReplicasController::refresh);
  t->start(3000);
}

void ReplicasController::add_replica(Replica *r) {
  r->setParent(this);
  replicas_.push_back(r);
  connect(r, &QObject::destroyed, this,
          [&](QObject *o) { replicas_.removeAll(qobject_cast<Replica *>(o)); });
}

void ReplicasController::refresh() { emit refreshed(); }
