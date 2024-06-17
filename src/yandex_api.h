#ifndef YANDEX_API_H
#define YANDEX_API_H

#include <QObject>

class QOAuth2AuthorizationCodeFlow;

class Settings;

class YandexApi : public QObject
{
    Q_OBJECT
public:
    explicit YandexApi(Settings &settings, QObject *parent = nullptr);

    bool check();

public slots:
    void grant();
    void test();

signals:
    void authenticated();

private:
    QOAuth2AuthorizationCodeFlow *oauth2_;
    Settings &settings_;
};

#endif // YANDEX_API_H
