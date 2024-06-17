#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

#include "settings.h"

class Application : public QApplication
{
    Q_OBJECT
public:
    Application(int &argc, char **argv);
    ~Application(){};

    void init();

    Settings& settings();
private:
    Settings* settings_;
};

#endif // APPLICATION_H
