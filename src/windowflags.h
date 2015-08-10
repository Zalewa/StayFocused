#ifndef idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe
#define idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe

#include <QMap>
#include <QString>
#include <windows.h>
#include "flags.h"

class WindowFlags
{
public:
    class Style
    {
    public:
        Flags<LONG> flags;

        Style();
        Style(LONG flags);

        static const QMap<LONG, QString> &flagsDefs();
        static QString name(LONG flag);

        bool hasFlag(LONG flag) const;
    };

    WindowFlags(HWND hwnd);
    ~WindowFlags();

    Style style() const;
    void setStyle(LONG flags);
    void setStyleFlags(LONG flags, bool set);

private:
    class PrivData;
    PrivData *d;
};

#endif
