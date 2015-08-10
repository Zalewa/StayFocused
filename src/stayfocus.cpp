#include "stayfocus.h"

#include <windows.h>
#include <QDebug>
#include <QTimer>
#include "mainwindow.h"
#include "processlist.h"
#include "winapi.h"

class StayFocus::PrivData
{
public:
    QString error;
    bool focusing;
    HWND hwnd;
    QTimer focusTimer;
    QSet<HWND> ignore;
};


StayFocus::StayFocus(QObject *parent)
    : QObject(parent)
{
    d = new PrivData();
    d->focusing = false;
    this->connect(&d->focusTimer, SIGNAL(timeout()), SLOT(focus()));
    d->focusTimer.setInterval(500);
}

StayFocus::~StayFocus()
{
    delete d;
}

void StayFocus::addIgnore(HWND ignore)
{
    d->ignore.insert(ignore);
}

void StayFocus::clearIgnore()
{
    d->ignore.clear();
}

bool StayFocus::isFocusing() const
{
    return d->focusing;
}

void StayFocus::startFocus(HWND hwnd)
{
    if (hwnd == NULL)
    {
        d->error = tr("No window specified.");
        return;
    }
    bool prevState = d->focusing;
    d->error = QString();
    d->hwnd = hwnd;
    d->focusing = true;
    d->focusTimer.start();
    if (prevState != d->focusing)
    {
        emit focusingChanged(true);
    }
}

void StayFocus::stopFocus()
{
    d->focusTimer.stop();
    bool prevState = d->focusing;
    d->focusing = false;
    if (prevState != d->focusing)
    {
        emit focusingChanged(false);
    }
}

void StayFocus::focus()
{
    if (d->ignore.contains(GetForegroundWindow()) || d->hwnd == GetForegroundWindow())
    {
        return;
    }

    QList<DWORD> remoteThreads = listWindowsThreads();
    attachRemoteThreads(remoteThreads, true);
    SetActiveWindow(d->hwnd);
    attachRemoteThreads(remoteThreads, false);
}

QList<DWORD> StayFocus::listWindowsThreads()
{
    QList<DWORD> threads;
    ProcessList list;
    QList<WindowEntry> windows = list.listWindows();
    foreach (const auto &window, windows)
    {
        threads << GetWindowThreadProcessId(window.hwnd, NULL);
    }
    return threads;
}

void StayFocus::attachRemoteThreads(const QList<DWORD> &threads, bool attach)
{
    DWORD currentThread = GetCurrentThreadId();
    foreach (const auto &thread, threads)
    {
        if (currentThread != thread)
        {
            AttachThreadInput(currentThread, thread, attach);
        }
    }
}

QString StayFocus::error() const
{
    return d->error;
}
