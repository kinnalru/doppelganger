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
  QVariant name##_;                                                            \
  Q_PROPERTY(value_type name MEMBER name##_ READ name WRITE set_##name RESET   \
                 reset_##name)                                                 \
public:                                                                        \
  value_type name() const {                                                    \
    qDebug() << "PROP:" << this << name##_.isNull();                           \
    if (name##_.isNull()) {                                                    \
      return default_##name();                                                 \
    }                                                                          \
    return name##_.value<value_type>();                                        \
  };                                                                           \
  void set##_name(const value_type &val) {                                     \
    name##_ = QVariant::fromValue(val);                                        \
  }                                                                            \
  value_type default_##name() const { return value_type(default_value); }      \
  void reset_##name() { name##_ = QVariant(); }

class Replica : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString path MEMBER path_ READ path WRITE set_path)
  GENERATE_PROPERTY(name, QString, "")
public:
  explicit Replica() {};

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

#endif // UNISON_H
