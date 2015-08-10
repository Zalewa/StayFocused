#ifndef idfd9ed23d_5a4b_4371_aef4_1b09b4268467
#define idfd9ed23d_5a4b_4371_aef4_1b09b4268467

#include <windows.h>
#include <QList>
#include <QString>

namespace Winapi
{
    QString errorMessage(int error);
    QList<HWND> snapshotWindows();
    void setWindowLong(HWND hwnd, int index, LONG value);
}

#endif
