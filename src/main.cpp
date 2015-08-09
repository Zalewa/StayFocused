#include "main.h"

#include <QApplication>
#include "mainwindow.h"

int Main::run()
{
    QApplication *app = new QApplication(argc, argv);
    MainWindow *window = new MainWindow();
    window->show();
    int rc = app->exec();
    delete window;
    return rc;
}
