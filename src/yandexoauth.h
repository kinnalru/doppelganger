#ifndef YANDEXOAUTH_H
#define YANDEXOAUTH_H

#include <QObject>

class QOAuth2AuthorizationCodeFlow;

class YandexOauth : public QObject
{
    Q_OBJECT
public:
    explicit YandexOauth(QObject *parent = nullptr);
    explicit YandexOauth(const QString &clientIdentifier, QObject *parent = nullptr);



public slots:
    void grant();
    void test();

signals:
    void authenticated();

private:
    QOAuth2AuthorizationCodeFlow* oauth2;
};

#endif // YANDEXOAUTH_H
