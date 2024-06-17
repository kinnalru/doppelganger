#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    explicit Settings(QSettings::Format format,
                      QSettings::Scope scope,
                      const QString &organization,
                      const QString &application = QString(),
                      QObject *parent = nullptr);

    const QString &yandexClientIdentifier() const;
    const QString &yandexClientSecret() const;
    QString yandexAccessToken() const;
    QString yandexRefreshToken() const;

    void setYandexAccessToken(const QString &token);
    void setYandexRefreshToken(const QString &token);

private:
    static const QString yandexClientIdentifier_;
    static const QString yandexClientSecret_;
};

#endif // SETTINGS_H
