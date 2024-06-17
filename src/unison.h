#ifndef UNISON_H
#define UNISON_H

#include <QJsonObject>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QVariant>

class Unison : public QObject
{
    Q_OBJECT
public:
    explicit Unison(QObject *parent = nullptr);

signals:
};

#define GENERATE_PROPERTY(name, value_type, default_value) \
private: \
    Q_PROPERTY(value_type name READ name WRITE name##_set RESET name##_reset) \
signals: \
    void name##_changed(const value_type &); \
\
public: \
    value_type name() const \
    { \
        QVariant v = QObject::property("##name##"); \
        if (v.isNull()) { \
            return name##_default(); \
        } \
        return v.value<value_type>(); \
    }; \
    bool name##_set(const value_type &val) \
    { \
        return QObject::setProperty("##name##", QVariant::fromValue(val)); \
    } \
    value_type name##_default() const \
    { \
        return value_type(default_value); \
    } \
    void name##_reset() \
    { \
        QObject::setProperty("##name##", QVariant()); \
    }

class Replica : public QObject
{
    Q_OBJECT
    GENERATE_PROPERTY(name, QString, "")
public:
    explicit Replica(){};

    QJsonObject to_json()
    {
        // QJsonObject json;

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
