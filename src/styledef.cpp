#include "styledef.h"

using namespace Def;

const QMap<LONG, QString> &StyleDef::wsStyles()
{
    static QMap<LONG, QString> m;
    if (m.isEmpty())
    {
        m.insert(WS_OVERLAPPED, tr("WS_OVERLAPPED"));
        m.insert(WS_POPUP, tr("WS_POPUP"));
        m.insert(WS_CHILD, tr("WS_CHILD"));
        m.insert(WS_MINIMIZE, tr("WS_MINIMIZE"));
        m.insert(WS_VISIBLE, tr("WS_VISIBLE"));
        m.insert(WS_DISABLED, tr("WS_DISABLED"));
        m.insert(WS_CLIPSIBLINGS, tr("WS_CLIPSIBLINGS"));
        m.insert(WS_CLIPCHILDREN, tr("WS_CLIPCHILDREN"));
        m.insert(WS_MAXIMIZE, tr("WS_MAXIMIZE"));
        m.insert(WS_CAPTION, tr("WS_CAPTION"));
        m.insert(WS_BORDER, tr("WS_BORDER"));
        m.insert(WS_DLGFRAME, tr("WS_DLGFRAME"));
        m.insert(WS_VSCROLL, tr("WS_VSCROLL"));
        m.insert(WS_HSCROLL, tr("WS_HSCROLL"));
        m.insert(WS_SYSMENU, tr("WS_SYSMENU"));
        m.insert(WS_THICKFRAME, tr("WS_THICKFRAME"));
        m.insert(WS_GROUP, tr("WS_GROUP"));
        m.insert(WS_TABSTOP, tr("WS_TABSTOP"));
        m.insert(WS_MINIMIZEBOX, tr("WS_MINIMIZEBOX"));
        m.insert(WS_MAXIMIZEBOX, tr("WS_MAXIMIZEBOX"));
    }
    return m;
}

const QMap<LONG, QString> &StyleDef::wsExStyles()
{
    static QMap<LONG, QString> m;
    if (m.isEmpty())
    {
        m.insert(WS_EX_DLGMODALFRAME, tr("WS_EX_DLGMODALFRAME"));
        m.insert(WS_EX_NOPARENTNOTIFY, tr("WS_EX_NOPARENTNOTIFY"));
        m.insert(WS_EX_TOPMOST, tr("WS_EX_TOPMOST"));
        m.insert(WS_EX_ACCEPTFILES, tr("WS_EX_ACCEPTFILES"));
        m.insert(WS_EX_TRANSPARENT, tr("WS_EX_TRANSPARENT"));
        m.insert(WS_EX_MDICHILD, tr("WS_EX_MDICHILD"));
        m.insert(WS_EX_TOOLWINDOW, tr("WS_EX_TOOLWINDOW"));
        m.insert(WS_EX_WINDOWEDGE, tr("WS_EX_WINDOWEDGE"));
        m.insert(WS_EX_CLIENTEDGE, tr("WS_EX_CLIENTEDGE"));
        m.insert(WS_EX_CONTEXTHELP, tr("WS_EX_CONTEXTHELP"));
        m.insert(WS_EX_RIGHT, tr("WS_EX_RIGHT"));
        m.insert(WS_EX_LEFT, tr("WS_EX_LEFT"));
        m.insert(WS_EX_RTLREADING, tr("WS_EX_RTLREADING"));
        m.insert(WS_EX_LTRREADING, tr("WS_EX_LTRREADING"));
        m.insert(WS_EX_LEFTSCROLLBAR, tr("WS_EX_LEFTSCROLLBAR"));
        m.insert(WS_EX_RIGHTSCROLLBAR, tr("WS_EX_RIGHTSCROLLBAR"));
        m.insert(WS_EX_CONTROLPARENT, tr("WS_EX_CONTROLPARENT"));
        m.insert(WS_EX_STATICEDGE, tr("WS_EX_STATICEDGE"));
        m.insert(WS_EX_APPWINDOW, tr("WS_EX_APPWINDOW"));
        m.insert(WS_EX_OVERLAPPEDWINDOW, tr("WS_EX_OVERLAPPEDWINDOW"));
        m.insert(WS_EX_PALETTEWINDOW, tr("WS_EX_PALETTEWINDOW"));
        m.insert(WS_EX_LAYERED, tr("WS_EX_LAYERED"));
        m.insert(WS_EX_NOINHERITLAYOUT, tr("WS_EX_NOINHERITLAYOUT"));
        m.insert(WS_EX_LAYOUTRTL, tr("WS_EX_LAYOUTRTL"));
        m.insert(WS_EX_COMPOSITED, tr("WS_EX_COMPOSITED"));
        m.insert(WS_EX_NOACTIVATE, tr("WS_EX_NOACTIVATE"));
    }
    return m;
}
