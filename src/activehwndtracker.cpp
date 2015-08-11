#include "activehwndtracker.h"

#include <QDebug>
#include <QMap>
#include "hook.h"

class ActiveHwndTracker::PrivData
{
public:
    QList<HWND> history;
};

ActiveHwndTracker::ActiveHwndTracker(QObject *parent)
    : QObject(parent)
{
    d = new PrivData();
    Hook *hook = new Hook(this);
    this->connect(hook, SIGNAL(activated(HookEvent)), SLOT(snapshot(HookEvent)));
    hook->hookEvent(EVENT_SYSTEM_FOREGROUND);
}

ActiveHwndTracker::~ActiveHwndTracker()
{
    delete d;
}

void ActiveHwndTracker::snapshot(const HookEvent &event)
{
    d->history.removeAll(event.hwnd);
    d->history << event.hwnd;
}

QList<HWND> ActiveHwndTracker::history() const
{
    return d->history;
}
