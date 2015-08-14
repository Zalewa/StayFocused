#ifndef idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe
#define idc5e3acaf_e20b_42b2_9d79_4ea4879cbfbe

#include <QMap>
#include <QRect>
#include <QString>
#include <windows.h>
#include "flags.h"

class Window
{
public:
    Window(HWND hwnd);
    ~Window();

    FlagSet<LONG> style() const;
    void setStyle(LONG flags);
    void setStyleFlags(LONG flags, bool set);

    FlagSet<LONG> exStyle() const;
    void setExStyle(LONG flags);

    void minimize();
    void maximize();
    void showNormal();

    QRect rect() const;
    void setRect(int x, int y, int width, int height);

    void setTopmost(bool b);

private:
    class PrivData;
    PrivData *d;
};

#endif
