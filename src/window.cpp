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

void Window::minimize()
{
    ShowWindow(d->hwnd, SW_MINIMIZE);
}

void Window::maximize()
{
    ShowWindow(d->hwnd, SW_MAXIMIZE);
}

void Window::showNormal()
{
    ShowWindow(d->hwnd, SW_RESTORE);
}

QRect Window::rect() const
{
    RECT rect;
    GetWindowRect(d->hwnd, &rect);
    return QRect(rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top);
}

void Window::setRect(int x, int y, int width, int height)
{
    SetWindowPos(d->hwnd, d->hwnd, x, y, width, height, SWP_NOZORDER | SWP_NOACTIVATE);
}

void Window::setTopmost(bool b)
{
    HWND position = b ? HWND_TOPMOST : HWND_NOTOPMOST;
    SetWindowPos(d->hwnd, position, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
