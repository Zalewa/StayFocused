#include "stayfocus.h"

#include <windows.h>
#include <QDebug>
#include "hook.h"
#include "mainwindow.h"
#include "processlist.h"
#include "winapi.h"

class StayFocus::PrivData
{
public:
    QString error;
    bool focusing;
    HWND hwnd;
    QSet<HWND> ignore;
};


StayFocus::StayFocus(QObject *parent)
    : QObject(parent)
{
    d = new PrivData();
    d->focusing = false;

    Hook *hook = new Hook(this);
    this->connect(hook, SIGNAL(activated(HookEvent)), SLOT(snap(HookEvent)));
    hook->hookEvent(EVENT_SYSTEM_FOREGROUND);
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
    if (prevState != d->focusing)
    {
        emit focusingChanged(true);
    }
}

void StayFocus::stopFocus()
{
    bool prevState = d->focusing;
    d->focusing = false;
    if (prevState != d->focusing)
    {
        emit focusingChanged(false);
    }
}

void StayFocus::snap(const HookEvent &event)
{
    if (isIgnored(event.hwnd))
    {
        return;
    }

    QList<DWORD> remoteThreads = listWindowsThreads();
    attachRemoteThreads(remoteThreads, true);
    SetActiveWindow(d->hwnd);
    attachRemoteThreads(remoteThreads, false);
}

bool StayFocus::isIgnored(HWND hwnd) const
{
    return d->ignore.contains(hwnd) || d->hwnd == hwnd || !d->focusing;
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
