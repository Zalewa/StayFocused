#include "hook.h"

#include <QMap>
#include "winapi.h"

class Hook::PrivData
{
public:
    static QMap<HWINEVENTHOOK, Hook*> hooks;

    QString error;
    HWINEVENTHOOK hook;

    void storeError()
    {
        if (GetLastError() != ERROR_SUCCESS)
        {
            error = Winapi::errorMessage(GetLastError());
        }
        else
        {
            error = QString();
        }
    }
};

QMap<HWINEVENTHOOK, Hook*> Hook::PrivData::hooks;


Hook::Hook(QObject *parent)
    : QObject(parent)
{
    d = new PrivData();
    d->hook = 0;
}

Hook::~Hook()
{
    unhook();
    delete d;
}

void Hook::onHook(DWORD event, HWND hwnd, LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime)
{
    HookEvent e;
    e.event = event;
    e.hwnd = hwnd;
    e.idObject = idObject;
    e.idChild = idChild;
    e.dwEventThread = dwEventThread;
    e.dwmsEventTime = dwmsEventTime;
    emit activated(e);
}

const QString &Hook::error() const
{
    return d->error;
}

bool Hook::hookEvent(UINT event)
{
    d->hook = SetWinEventHook(event, event, NULL, HookCallback::winEventProc,
        0, 0, WINEVENT_OUTOFCONTEXT);
    if (d->hook != 0)
    {
        PrivData::hooks.insert(d->hook, this);
    }
    d->storeError();
    return d->hook != 0;
}

void Hook::unhook()
{
    if (d->hook != 0)
    {
        PrivData::hooks.remove(d->hook);
        UnhookWinEvent(d->hook);
        d->hook = 0;
    }
}

///////////////////////////////////////////////////////////////////////////

namespace HookCallback
{
void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event,
    HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime)
{
    Hook::PrivData::hooks[hWinEventHook]->onHook(
        event, hwnd, idObject, idChild, dwEventThread, dwmsEventTime);
}
}
