#include "activehwndtracker.h"

#include <QDebug>
#include <QMap>

class ActiveHwndTracker::PrivData
{
public:
    static QMap<HWINEVENTHOOK, ActiveHwndTracker*> hooks;

    QList<HWND> history;
    HWINEVENTHOOK hook;
};

QMap<HWINEVENTHOOK, ActiveHwndTracker*> ActiveHwndTracker::PrivData::hooks;

namespace ActiveHwndTrackerCallback
{

void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
    LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
    ActiveHwndTracker::PrivData::hooks[hWinEventHook]->onHook(
        event, hwnd, idObject, idChild, dwEventThread, dwmsEventTime);
}

}


ActiveHwndTracker::ActiveHwndTracker(QObject *parent)
    : QObject(parent)
{
    d = new PrivData();
    d->hook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL,
        ActiveHwndTrackerCallback::winEventProc, 0, 0,
        WINEVENT_OUTOFCONTEXT);
    if (d->hook != 0)
    {
        PrivData::hooks.insert(d->hook, this);
    }
}

ActiveHwndTracker::~ActiveHwndTracker()
{
    if (d->hook != 0)
    {
        PrivData::hooks.remove(d->hook);
        UnhookWinEvent(d->hook);
    }
    delete d;
}

void ActiveHwndTracker::onHook(DWORD event, HWND hwnd, LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime)
{
    d->history.removeAll(hwnd);
    d->history << hwnd;
}

QList<HWND> ActiveHwndTracker::history() const
{
    return d->history;
}
