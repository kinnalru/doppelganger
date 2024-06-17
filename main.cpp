#include "mainwindow.h"

#include "application.h"
#include <QLocale>
#include <QTranslator>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>
#include <QIODevice>
// #include <QOAuth2AuthorizationCodeFlow>
//#include <QtNetworkAuth/qoauth2authorizationcodeflow.h>


bool readSettingsJson(QIODevice &device, QMap<QString, QVariant> &map);
bool writeSettingsJson(QIODevice &device, const QMap<QString, QVariant> &map);



static const QSettings::Format JsonFormat = QSettings::registerFormat("json", &readSettingsJson, &writeSettingsJson);

int main(int argc, char *argv[])
{
    Application app(argc, argv);

    app.setOrganizationName("jerry_ru");
    app.setApplicationName("doppelganger");

    app.setQuitOnLastWindowClosed(false);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "mirror_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            app.installTranslator(&translator);
            break;
        }
    }

    auto qs = QSettings(JsonFormat, QSettings::UserScope, app.organizationName(), app.applicationName(), &app);

    qs.setValue("test", 123);

       qs.setValue("group/test", 123);

    MainWindow w;
    w.show();

    // unison-text -group  -times -acl -xattrs -copyonconflict -batch -clientHostName=clietn -fastcheck true -rootalias "//jerrybook//home/jerry/Documents/mirror/1 -> a1" -batch /home/jerry/Documents/mirror/1 /home/jerry/Documents/mirror/2
    return app.exec();
}

void paraseJsonObject(QJsonObject &json, QString prefix, QMap<QString, QVariant> &map)
{
    QJsonValue value;
    QJsonObject obj;

    QStringList keys = json.keys();
    for(int i=0; i<keys.size(); i++)
    {
        value = json.value(keys[i]);
        if(value.isObject())
        {
            obj = value.toObject();
            paraseJsonObject(obj, prefix+keys[i]+"/", map);
        }
        else
        {
            map.insert(prefix+keys[i], value.toVariant());
        }
    }
}

QJsonObject restoreJsonObject(QMap<QString, QVariant> &map)
{
    QJsonObject obj;
    QStringList keys = map.keys();

    for(int i=0; i<keys.size(); i++)
    {
        QString key = keys.at(i);
        QVariant value = map.value(key);
        QStringList sections = key.split('/');
        if(sections.size() > 1)
        {
            continue;
        }
        else
        {
            map.remove(key);
            obj.insert(key, QJsonValue::fromVariant(value));
        }
    }

    QList<QMap<QString, QVariant>> subMaps;
    keys = map.keys();
    for(int i=0; i<keys.size(); i++)
    {
        bool found = false;
        QString key = keys[i];

        for(int j=0; j<subMaps.size(); j++)
        {
            QString subKey = subMaps[j].key(QString("__key__"));
            if(subKey.contains(key.section('/', 0, 0)))
            {
                subMaps[j].insert(key.section('/', 1), map.value(key));
                found = true;
                break;
            }
        }

        if(!found)
        {
            QMap<QString, QVariant> tmp;
            tmp.insert(key.section('/', 0, 0), QString("__key__"));
            tmp.insert(key.section('/', 1), map.value(key));
            subMaps.append(tmp);
        }
    }

    for(int i=0; i<subMaps.size(); i++)
    {
        QString key = subMaps[i].key(QString("__key__"));
        subMaps[i].remove(key);

        QJsonObject tmp = restoreJsonObject(subMaps[i]);
        obj.insert(key, tmp);
    }
    return obj;
}

bool readSettingsJson(QIODevice &device, QMap<QString, QVariant> &map)
{
    QJsonParseError jsonError;
    QJsonObject obj = QJsonDocument::fromJson(device.readAll(), &jsonError).object();
    if(jsonError.error != QJsonParseError::NoError)
        return false;

    paraseJsonObject(obj, QString(), map);
    return true;
}

bool writeSettingsJson(QIODevice &device, const QMap<QString, QVariant> &map)
{
    QMap<QString, QVariant> tmp_map = map;
    QJsonObject buffer = restoreJsonObject(tmp_map);
    device.write(QJsonDocument(buffer).toJson());
    return true;
}
