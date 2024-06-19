#ifndef REPLICAS_CONFIG_H
#define REPLICAS_CONFIG_H

#include <QObject>

namespace Replicas {

class Config : public QObject {
  Q_OBJECT
public:
  explicit Config(QObject *parent = nullptr);

signals:
};
} // namespace Replicas

#endif // REPLICAS_CONFIG_H
