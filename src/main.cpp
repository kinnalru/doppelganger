#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>
#include <QSettings>
#include <QTranslator>
#include "application.h"

#include <QJsonDocument>
#include <QTimer>

#include <QDebug>

#include "mainwindow.h"

#include "yandex_api.h"

#include "unison.h"

#include <QtGui/qdesktopservices.h>

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    app.setOrganizationName("doppelganger");
    app.setApplicationName("doppelganger");

    app.setQuitOnLastWindowClosed(true);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "mirror_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    // auto qs = QSettings(QtJsonSettings::format(), QSettings::UserScope, app.organizationName(), app.applicationName(), &app);

    app.settings().setValue("test", 123);

    qDebug() << app.settings().fileName();

    //    qs.setValue("group/test", 123);

    MainWindow w;
    w.show();

    qDebug() << "hello";

    auto r = Replica();

    r.name_set("nnnnnnnnammmmeee");
    qDebug() << "name0:" << r.name();
    r.setProperty("name", "1111111");
    qDebug() << "name1:" << r.name();

    qDebug() << QJsonDocument(r.to_json()).toJson();
    r.name_reset();
    qDebug() << "name2:" << r.name();

    auto yo = new YandexApi(app.settings(), &app);
    // yo->check();
    // yo->grant();

    // QDesktopServices::openUrl(QUrl("https://ya.ru"));

    // unison-text -group  -times -acl -xattrs -copyonconflict -batch -clientHostName=clietn -fastcheck true -rootalias "//jerrybook//home/jerry/Documents/mirror/1 -> a1" -batch /home/jerry/Documents/mirror/1 /home/jerry/Documents/mirror/2
    return app.exec();
}
