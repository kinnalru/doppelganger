#include "application.h"
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLocale>
#include <QSettings>
#include <QTranslator>

#include <QJsonDocument>
#include <QTimer>

#include <QDebug>

#include "mainwindow.h"

#include "yandex_api.h"

#include "replicas_controller.h"
#include "unison.h"

#include "replicas/config_provider.h"

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

    // auto qs = QSettings(QtJsonSettings::format(), QSettings::UserScope,
    // app.organizationName(), app.applicationName(), &app);

    app.settings().setValue("test", 123);

    qDebug() << app.settings().replicasConfigPath();

    auto p = Replicas::ConfigProvider(app.settings().replicasConfigPath());
    ;

    p.add_replica("NAME3");

    //    qs.setValue("group/test", 123);

    MainWindow w;
    w.show();

    qDebug() << "hello";

    auto r1 = new Replica();

    r1->set_path("/tmp/replica1");
    r1->set_name("replica1");
    qDebug() << QJsonDocument(r1->to_json()).toJson();

    auto r2 = new Replica();

    r2->set_path("/tmp/replica2");
    r2->set_name("replica2");
    qDebug() << QJsonDocument(r2->to_json()).toJson();

    auto controller = new ReplicasController(&app);

    QList<Replica *> replicas;
    replicas.append(r1);
    replicas.append(r2);

    for (Replica *r : replicas) {
        qDebug() << QJsonDocument(r->to_json()).toJson();
        controller->add_replica(r);
        w.add_replica(r);
    }

    QObject::connect(controller, &ReplicasController::refreshed, &w, &MainWindow::refreshed);

    auto yo = new YandexApi(app.settings(), &app);
    // yo->check();
    // yo->grant();

    // QDesktopServices::openUrl(QUrl("https://ya.ru"));

    // unison-text -group  -times -acl -xattrs -copyonconflict -batch
    // -clientHostName=clietn -fastcheck true -rootalias
    // "//jerrybook//home/jerry/Documents/mirror/1 -> a1" -batch
    // /home/jerry/Documents/mirror/1 /home/jerry/Documents/mirror/2
    return app.exec();
}
