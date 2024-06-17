// #include <QTextCodec>

#include "application.h"

Application::Application(int &argc, char **argv)
    : QApplication(argc, argv)
{
    init();
}

void Application::init()
{
    this->setOrganizationName("urtcommunity");
    this->setApplicationName("urtconnector");

    //Initializing main settings
    // base_settings set;
    // set.register_group( app_settings::uid(),   "app_opts",   "options.ini" );

    // loading translations
    // static boost::shared_ptr<QTranslator> qt_trans = system_translator( app_settings().country_name() );

    // if ( !qt_trans->isEmpty() )
    {
        // LOG_DEBUG << "Qt translation \"%1\" loaded", app_settings().country_name();
    }
    // else
    {
        // LOG_DEBUG << "Failed to load Qt translation \"%1\". Trying \"%2\" instead...", app_settings().country_name(), QLocale::system().name();

        // qt_trans = system_translator( QLocale::system().name() );
        // if( !qt_trans->isEmpty() )
        // LOG_DEBUG << "Qt translation \"%1\" loaded", QLocale::system().name();
        // else
        // LOG_DEBUG << "Failed to load Qt translation \"%1\"", QLocale::system().name();
    }

    // a->installTranslator(qt_trans.get());

    // static boost::shared_ptr<QTranslator> urt_tr = local_translator( app_settings().country_name() );

    // if ( !urt_tr->isEmpty()  )
    {
        // LOG_DEBUG << "Application translation \"%1\" loaded", app_settings().country_name();
    }
    // else
    {
        // LOG_DEBUG << "Failed to load application translation \"%1\"", app_settings().country_name();
    }

    // a->installTranslator(urt_tr.get());

    // QTextCodec::setCodecForTr( QTextCodec::codecForName("utf8") );

    // set.register_group( clip_settings::uid(),  "clipboard",  "options.ini" );
    // set.register_group( qstat_options::uid(), "qstat_opts", "options.ini" );

    // //Registering state_settings in separate file
    // set.register_file( state_settings::uid(), "state.ini" );
    // set.register_group( rcon_settings::uid(), "rcon", "options.ini" );
    // set.register_group( anticheat::settings::uid(), "anticheat", "options.ini" );

    // set.register_file( "history", "history.ini" );

    //Initializing resource resolution
    // to use icons from resources you must use "icons:<name>" syntax
    // other resource syntax unchaged

    // detect christmas and using icons from another iconset
    // if( is_christmas_mode() )
    // {
    //     QDir::addSearchPath("icons", QString(":icons/icons/christmas"));
    //     QDir::addSearchPath("images", QString(":images/icons/christmas"));
    // }

    // QDir::addSearchPath("icons", QString(":icons/icons/"));
    // QDir::addSearchPath("images", QString(":images/icons/"));

    this->translate("language", "Russian");
    this->translate("language", "English");
    this->translate("language", "kitaiskij");

    // app_settings().default_style_name_set(QApplication::style()->objectName());
    // QApplication::setStyle(app_settings().style_name());
}


