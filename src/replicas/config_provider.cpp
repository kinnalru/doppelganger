
#include "config_provider.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QSettings>

namespace Replicas {

ConfigProvider::ConfigProvider(const QString &path, QObject *parent)
    : QObject{parent}
{
    config_ = new QSettings(path, QSettings::defaultFormat());

    list_ = QJsonArray::fromVariantList(
        config_->value("replicas", QVariantList()).value<QVariantList>());

    QStringList replicas;

    for (const QJsonValue &v : list_) {
        replicas.push_back(v.toObject().value("name").toString());
    }

    emit refresh(replicas);
}

void ConfigProvider::add_replica(const QString &name)
{
    list_.push_back(QJsonObject({{"name", name}}));
    config_->setValue("replicas", list_);
}

} // namespace Replicas
