#include "windowflags.h"

#include <QMap>
#include <QString>
#include "styledef.h"

class WindowFlags::PrivData
{
public:
    HWND hwnd;
};


WindowFlags::WindowFlags(HWND hwnd)
{
    d = new PrivData();
    d->hwnd = hwnd;
}

WindowFlags::~WindowFlags()
{
    delete d;
}

FlagSet<LONG> WindowFlags::style() const
{
    return FlagSet<LONG>(Def::StyleDef::wsStyles(), GetWindowLong(d->hwnd, GWL_STYLE));
}

void WindowFlags::setStyle(LONG flags)
{
    Winapi::setWindowLong(d->hwnd, GWL_STYLE, flags);
}

void WindowFlags::setStyleFlags(LONG flags, bool set)
{
    Flags<LONG> currentFlags = style().flags;
    currentFlags.set(flags, set);
    setStyle(currentFlags);
}

FlagSet<LONG> WindowFlags::exStyle() const
{
    return FlagSet<LONG>(Def::StyleDef::wsExStyles(), GetWindowLong(d->hwnd, GWL_EXSTYLE));
}

void WindowFlags::setExStyle(LONG flags)
{
    Winapi::setWindowLong(d->hwnd, GWL_EXSTYLE, flags);
}
