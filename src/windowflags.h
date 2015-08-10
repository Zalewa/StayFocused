#ifndef idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe
#define idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe

#include <QMap>
#include <QString>
#include <windows.h>
#include "flags.h"

class WindowFlags
{
public:
    WindowFlags(HWND hwnd);
    ~WindowFlags();

    FlagSet<LONG> style() const;
    void setStyle(LONG flags);
    void setStyleFlags(LONG flags, bool set);

    FlagSet<LONG> exStyle() const;
    void setExStyle(LONG flags);

private:
    class PrivData;
    PrivData *d;
};

#endif
