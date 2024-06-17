
#include <QtNetworkAuth/qoauth2authorizationcodeflow.h>
#include <QtNetworkAuth/qoauthhttpserverreplyhandler.h>

#include <QtGui/qdesktopservices.h>

#include <QDebug>

#include <QNetworkReply>

#include "yandexoauth.h"

using namespace Qt::StringLiterals;

// static constexpr auto hotUrl("https://oauth.reddit.com/hot"_L1);
static constexpr auto authorizationUrl("https://oauth.yandex.ru/authorize"_L1);
static constexpr auto accessTokenUrl("https://oauth.yandex.ru/token"_L1);
static constexpr auto scope("cloud_api:disk.app_folder"_L1);

YandexOauth::YandexOauth(QObject *parent) : QObject{parent} {
  oauth2 = new QOAuth2AuthorizationCodeFlow(this);
  auto replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
  oauth2->setReplyHandler(replyHandler);
  oauth2->setAuthorizationUrl(QUrl(authorizationUrl));
  oauth2->setAccessTokenUrl(QUrl(accessTokenUrl));
  oauth2->setScope(scope);
  oauth2->setClientIdentifierSharedKey("d6d6703e2fe046d09d7c6e5f01481f54");

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::requestFailed, this,
          [](const QAbstractOAuth::Error error) {
            qDebug() << "requestFailed:" << int(error);
          });

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::statusChanged, this,
          [](const QAbstractOAuth::Status status) {
            qDebug() << "statusChanged:" << int(status);
          });

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::stateChanged, this,
          [](const QString &state) { qDebug() << "stateChanged:" << state; });

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::authorizationCallbackReceived,
          this, [](const QVariantMap &data) {
            qDebug() << "authorizationCallbackReceived:" << data;
          });

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::error, this,
          [](const QString &error, const QString &errorDescription,
             const QUrl &uri) {
            qDebug() << "error:" << error << " desc:" << errorDescription
                     << " uri:" << uri;
          });

  connect(oauth2, &QOAuth2AuthorizationCodeFlow::granted, this,
          &YandexOauth::test);
  connect(oauth2, &QOAuth2AuthorizationCodeFlow::granted, this,
          &YandexOauth::authenticated);
  connect(oauth2, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this,
          &QDesktopServices::openUrl);
}

YandexOauth::YandexOauth(const QString &clientIdentifier, QObject *parent)
    : YandexOauth(parent) {
  qDebug() << "try cleint:" << clientIdentifier;
  oauth2->setClientIdentifier(clientIdentifier);
}

void YandexOauth::test() {
  qDebug() << "GRANTED!!";
  qDebug() << "refresh:" << oauth2->refreshToken();
  qDebug() << "token:" << oauth2->token();
  qDebug() << "extra:" << oauth2->extraTokens();
  qDebug() << "expiration:" << oauth2->expirationAt();

  auto req = oauth2->get(QUrl("https://login.yandex.ru/info"));

  connect(req, &QNetworkReply::finished, this,
          [=]() { qDebug() << "info:" << req->readAll(); });
}

void YandexOauth::grant() {
  qDebug() << "start grant...";
  oauth2->grant();
}
