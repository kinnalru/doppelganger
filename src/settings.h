#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QSettings {
  Q_OBJECT
public:
  explicit Settings(QSettings::Scope scope, const QString &organization,
                    const QString &application = QString(),
                    QObject *parent = nullptr);

  const QString &yandexClientIdentifier() const;
  const QString &yandexClientSecret() const;

  void setYandexAccessToken(const QString &token);
  QString yandexAccessToken() const;

  void setYandexRefreshToken(const QString &token);
  QString yandexRefreshToken() const;

  QString replicasConfigPath() const;

private:
  static const QString yandexClientIdentifier_;
  static const QString yandexClientSecret_;
};

#endif // SETTINGS_H
