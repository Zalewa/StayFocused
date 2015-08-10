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

WindowFlags::Style WindowFlags::style() const
{
    return Style(GetWindowLong(d->hwnd, GWL_STYLE));
}

void WindowFlags::setStyle(LONG flags)
{
    SetLastError(ERROR_SUCCESS);
    SetWindowLong(d->hwnd, GWL_STYLE, flags);
    if (GetLastError() == ERROR_SUCCESS)
    {
        SetWindowPos(d->hwnd, d->hwnd, 0, 0, 0, 0,  SWP_NOMOVE | SWP_NOSIZE
            | SWP_NOZORDER | SWP_FRAMECHANGED);
    }
}

void WindowFlags::setStyleFlags(LONG flags, bool set)
{
    Flags<LONG> currentFlags = style().flags;
    currentFlags.set(flags, set);
    setStyle(currentFlags);
}

///////////////////////////////////////////////////////////////////////////

WindowFlags::Style::Style()
{
    this->flags = 0;
}

WindowFlags::Style::Style(LONG flags)
{
    this->flags = flags;
}

const QMap<LONG, QString> &WindowFlags::Style::flagsDefs()
{
    return Def::StyleDef::defs();
}

QString WindowFlags::Style::name(LONG flag)
{
    return flagsDefs()[flag];
}

bool WindowFlags::Style::hasFlag(LONG flag) const
{
    return (this->flags & flag) != 0;
}
