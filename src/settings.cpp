

#include "settings.h"

const QString Settings::yandexClientIdentifier_ = "7a9abeac6d0a491db7cfc8313448bc43";
const QString Settings::yandexClientSecret_ = "d6d6703e2fe046d09d7c6e5f01481f54";

Settings::Settings(QSettings::Format format,
                   QSettings::Scope scope,
                   const QString &organization,
                   const QString &application,
                   QObject *parent)
    : QSettings{format, scope, organization, application, parent}
{}

const QString &Settings::yandexClientIdentifier() const
{
    return yandexClientIdentifier_;
}

const QString &Settings::yandexClientSecret() const
{
    return yandexClientSecret_;
}

QString Settings::yandexAccessToken() const
{
    return value("yandex_disk/access_token").toString();
}

QString Settings::yandexRefreshToken() const
{
    return value("yandex_disk/refresh_token").toString();
}

void Settings::setYandexAccessToken(const QString &token)
{
    setValue("yandex_disk/access_token", token);
}

void Settings::setYandexRefreshToken(const QString &token)
{
    setValue("yandex_disk/refresh_token", token);
}
