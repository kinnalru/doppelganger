#ifndef REPLICAS_CONTROLLER_H
#define REPLICAS_CONTROLLER_H

#include <QList>
#include <QObject>

class Replica;

class ReplicasController : public QObject {
  Q_OBJECT
public:
  explicit ReplicasController(QObject *parent = nullptr);

  void add_replica(Replica *r);

public slots:
  void refresh();

signals:
  void refreshed();

private:
  QList<Replica *> replicas_;
};

#endif // REPLICAS_CONTROLLER_H
