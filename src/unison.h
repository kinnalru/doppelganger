#ifndef UNISON_H
#define UNISON_H

#include <QFileInfo>
#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

class Unison : public QObject {
  Q_OBJECT
public:
  explicit Unison(QObject *parent = nullptr);

signals:
};

#define GENERATE_PROPERTY(name, value_type, default_value)                     \
private:                                                                       \
  Q_PROPERTY(value_type name READ name WRITE set_##name RESET reset_##name)    \
public:                                                                        \
  value_type name() const {                                                    \
    QVariant v = QObject::property("##name##");                                \
    if (v.isNull()) {                                                          \
      return default_##name();                                                 \
    }                                                                          \
    return v.value<value_type>();                                              \
  };                                                                           \
  bool set##_name(const value_type &val) {                                     \
    return QObject::setProperty("##name##", QVariant::fromValue(val));         \
  }                                                                            \
  value_type default_##name() const { return value_type(default_value); }      \
  void reset_##name() { QObject::setProperty("##name##", QVariant()); }

class Replica : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString path READ path WRITE set_path)
  GENERATE_PROPERTY(name, QString, "")
public:
  explicit Replica(){};

  bool is_ready() { return QFileInfo(path() + "/" + ".doppelganger").exists(); }

  QString path() const {
    return QFileInfo(QObject::property("_path_").value<QString>())
        .canonicalFilePath();
  }

  bool set_path(const QString &path) {
    return QObject::setProperty(
        "_path_", QVariant::fromValue(QFileInfo(path).canonicalFilePath()));
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
};

#endif // UNISON_H
