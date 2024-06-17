
#include <QtNetworkAuth/qoauth2authorizationcodeflow.h>
#include <QtNetworkAuth/qoauthhttpserverreplyhandler.h>

#include <QtGui/qdesktopservices.h>

#include <QDebug>

#include <QNetworkReply>

#include "settings.h"
#include "yandex_api.h"

using namespace Qt::StringLiterals;

static constexpr auto authorizationUrl("https://oauth.yandex.ru/authorize"_L1);
static constexpr auto accessTokenUrl("https://oauth.yandex.ru/token"_L1);
static constexpr auto scope("cloud_api:disk.app_folder"_L1);

YandexApi::YandexApi(Settings &settings, QObject *parent)
    : QObject{parent}
    , settings_(settings)
{
    oauth2_ = new QOAuth2AuthorizationCodeFlow(this);
    oauth2_->setClientIdentifier(settings_.yandexClientIdentifier());
    oauth2_->setClientIdentifierSharedKey(settings_.yandexClientSecret());

    auto replyHandler = new QOAuthHttpServerReplyHandler(1337, this);
    oauth2_->setReplyHandler(replyHandler);

    oauth2_->setAuthorizationUrl(QUrl(authorizationUrl));
    oauth2_->setAccessTokenUrl(QUrl(accessTokenUrl));
    oauth2_->setScope(scope);

    if (!settings.yandexAccessToken().isEmpty()) {
        oauth2_->setToken(settings.yandexAccessToken());
    }

    if (!settings.yandexRefreshToken().isEmpty()) {
        oauth2_->setRefreshToken(settings.yandexRefreshToken());
    }

    connect(oauth2_,
            &QOAuth2AuthorizationCodeFlow::requestFailed,
            this,
            [](const QAbstractOAuth::Error error) { qDebug() << "requestFailed:" << int(error); });

    connect(oauth2_,
            &QOAuth2AuthorizationCodeFlow::statusChanged,
            this,
            [](const QAbstractOAuth::Status status) {
                qDebug() << "statusChanged:" << int(status);
            });

    connect(oauth2_, &QOAuth2AuthorizationCodeFlow::stateChanged, this, [](const QString &state) {
        qDebug() << "stateChanged:" << state;
    });

    connect(oauth2_,
            &QOAuth2AuthorizationCodeFlow::authorizationCallbackReceived,
            this,
            [](const QVariantMap &data) { qDebug() << "authorizationCallbackReceived:" << data; });

    connect(oauth2_,
            &QOAuth2AuthorizationCodeFlow::error,
            this,
            [](const QString &error, const QString &errorDescription, const QUrl &uri) {
                qDebug() << "error:" << error << " desc:" << errorDescription << " uri:" << uri;
            });

    connect(oauth2_, &QOAuth2AuthorizationCodeFlow::granted, this, &YandexApi::test);
    // connect(oauth2_, &QOAuth2AuthorizationCodeFlow::granted, this, &YandexApi::authenticated);
    connect(oauth2_,
            &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser,
            this,
            &QDesktopServices::openUrl);
}

bool YandexApi::check()
{
    oauth2_->refreshAccessToken();
    auto req = oauth2_->get(QUrl("https://login.yandex.ru/info"));
    connect(req, &QNetworkReply::finished, this, [=]() {
        qDebug() << "CHECK:" << int(req->error()) << req->readAll();

        qDebug() << "C refresh:" << oauth2_->refreshToken();
        qDebug() << "C token:" << oauth2_->token();
        qDebug() << "C extra:" << oauth2_->extraTokens();
        qDebug() << "C expiration:" << oauth2_->expirationAt();
    });
    return true;
}

// YandexApi::YandexApi(Settings& settings, QObject *parent)
//     : YandexApi(parent)
//     , settings_(settings)
// {
//   qDebug() << "try cleint:" << clientIdentifier;
//   oauth2->setClientIdentifier(clientIdentifier);
// }

void YandexApi::test()
{
    qDebug() << "GRANTED!!";
    qDebug() << "refresh:" << oauth2_->refreshToken();
    qDebug() << "token:" << oauth2_->token();
    qDebug() << "extra:" << oauth2_->extraTokens();
    qDebug() << "expiration:" << oauth2_->expirationAt();

    auto req = oauth2_->get(QUrl("https://login.yandex.ru/info"));

    connect(req, &QNetworkReply::finished, this, [=]() { qDebug() << "info:" << req->readAll(); });

    settings_.setYandexAccessToken(oauth2_->token());
    settings_.setYandexRefreshToken(oauth2_->refreshToken());
}

void YandexApi::grant()
{
    qDebug() << "start grant...";
    oauth2_->grant();
}
