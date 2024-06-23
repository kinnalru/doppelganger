#ifndef REPLICAS_CONFIG_PROVIDER_H
#define REPLICAS_CONFIG_PROVIDER_H

#include <QJsonArray>
#include <QObject>

class QSettings;

namespace Replicas {

class ConfigProvider : public QObject {
  Q_OBJECT
public:
  explicit ConfigProvider(const QString &path, QObject *parent = nullptr);

  void load();
  void save();

  void add_replica(const QString &name);
  void remove_replica(const QString &name);

signals:
  void refresh(const QStringList &);

private:
  QSettings *config_;
  QJsonArray list_;
};

} // namespace Replicas

#endif // REPLICAS_CONFIG_PROVIDER_H
