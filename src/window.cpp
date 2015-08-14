#include "window.h"

#include <QMap>
#include <QString>
#include "styledef.h"

class Window::PrivData
{
public:
    HWND hwnd;
};


Window::Window(HWND hwnd)
{
    d = new PrivData();
    d->hwnd = hwnd;
}

Window::~Window()
{
    delete d;
}

FlagSet<LONG> Window::style() const
{
    return FlagSet<LONG>(Def::StyleDef::wsStyles(), GetWindowLong(d->hwnd, GWL_STYLE));
}

void Window::setStyle(LONG flags)
{
    Winapi::setWindowLong(d->hwnd, GWL_STYLE, flags);
}

void Window::setStyleFlags(LONG flags, bool set)
{
    Flags<LONG> currentFlags = style().flags;
    currentFlags.set(flags, set);
    setStyle(currentFlags);
}

FlagSet<LONG> Window::exStyle() const
{
    return FlagSet<LONG>(Def::StyleDef::wsExStyles(), GetWindowLong(d->hwnd, GWL_EXSTYLE));
}

void Window::setExStyle(LONG flags)
{
    Winapi::setWindowLong(d->hwnd, GWL_EXSTYLE, flags);
}
