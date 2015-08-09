#include "trayicon.h"

#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include "mainwindow.h"

class TrayIcon::PrivData
{
public:
    MainWindow *parent;
    QSystemTrayIcon *trayIcon;
};


TrayIcon::TrayIcon(MainWindow *parent)
    : QObject(parent)
{
    d = new PrivData();
    d->parent = parent;
    this->connect(parent, SIGNAL(focusingChanged(bool)), SLOT(setFocusingIcon(bool)));

    d->trayIcon = new QSystemTrayIcon(this);

    QMenu *menu = new QMenu();
    qApp->connect(menu->addAction(tr("Quit")), SIGNAL(triggered()), SLOT(quit()));
    d->trayIcon->setContextMenu(menu);

    setIdleIcon();
    d->trayIcon->show();
}

TrayIcon::~TrayIcon()
{
    d->trayIcon->hide();
    delete d;
}

void TrayIcon::setFocusingIcon()
{
    d->trayIcon->setIcon(QIcon(":/icons/activated_64"));
}

void TrayIcon::setIdleIcon()
{
    d->trayIcon->setIcon(QIcon(":/icons/icon_64"));
}

void TrayIcon::setFocusingIcon(bool focusing)
{
    if (focusing)
    {
        setFocusingIcon();
    }
    else
    {
        setIdleIcon();
    }
}
