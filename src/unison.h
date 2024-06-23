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

#endif // UNISON_H
