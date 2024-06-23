#ifndef REPLICAS_UNIT_H
#define REPLICAS_UNIT_H

#include <QFileInfo>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>

#include "../macros.h"

namespace Replicas {

class Unit : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString path MEMBER path_ READ path WRITE set_path)
  GENERATE_PROPERTY(name, QString, "")
public:
  explicit Unit() {};

  bool is_ready() {
    qDebug() << "READY0" << this;
    qDebug() << "READY1" << path();
    return QFileInfo(path() + "/" + ".doppelganger").exists();
  }

  QString path() const { return QFileInfo(path_).canonicalFilePath(); }

  void set_path(const QString &path) {
    qDebug() << "set path" << path;
    path_ = QFileInfo(path).canonicalFilePath();
  }

  QJsonObject to_json() {
    QVariantMap map;
    auto mo = metaObject();
    for (int i = mo->propertyOffset(); i < mo->propertyCount(); ++i) {
      QVariant value = property(mo->property(i).name());
      map[mo->property(i).name()] = value;
    }

    return QJsonObject::fromVariantMap(map);
  }

private:
  QString path_;
};

} // namespace Replicas

#endif // REPLICAS_UNIT_H
