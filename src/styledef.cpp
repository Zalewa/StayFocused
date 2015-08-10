#include "styledef.h"

using namespace Def;

const QMap<LONG, QString> &StyleDef::defs()
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
