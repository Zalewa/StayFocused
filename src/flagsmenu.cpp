#include "flagsmenu.h"

#include <QDebug>
#include <QMessageBox>
#include "winapi.h"
#include "windowflags.h"

class FlagsMenu::PrivData
{
public:
    HWND hwnd;
};


FlagsMenu::FlagsMenu(HWND hwnd, QWidget *parent)
    : QMenu(parent)
{
    d = new PrivData();
    d->hwnd = hwnd;

    setup();
}

FlagsMenu::~FlagsMenu()
{
    delete d;
}

void FlagsMenu::setup()
{
    setupStyleMenu();
}

void FlagsMenu::setupStyleMenu()
{
    WindowFlags windowFlags(d->hwnd);
    FlagSet<LONG> style = windowFlags.style();
    QString error;
    if (GetLastError() != ERROR_SUCCESS)
    {
        error = Winapi::errorMessage(GetLastError());
    }

    QMenu *styleMenu = addMenu(tr("Style"));
    if (error.isNull())
    {
        this->connect(styleMenu, SIGNAL(triggered(QAction*)), SLOT(onStyleActionTriggered(QAction*)));
        foreach (LONG flag, style.names.keys())
        {
            QAction *action = styleMenu->addAction(style.name(flag));
            action->setData(flag);
            action->setCheckable(true);
            action->setChecked(style.flags.isSet(flag));
        }
    }
    else
    {
        styleMenu->addAction(tr("Error: %1").arg(error));
    }
}

void FlagsMenu::onStyleActionTriggered(QAction *action)
{
    LONG flag = static_cast<LONG>(action->data().toLongLong());
    WindowFlags windowFlags(d->hwnd);
    windowFlags.setStyleFlags(flag, action->isChecked());
    if (GetLastError() != ERROR_SUCCESS)
    {
        QMessageBox::critical(parentWidget(), tr("Style set error"),
            tr("Error: %1").arg(Winapi::errorMessage(GetLastError())));
    }
}
