#include "winapi.h"

#include <windows.h>

namespace Winapi
{

QList<HWND> snapshotHwnd;

QString errorMessage(int error)
{
    if (error == ERROR_SUCCESS)
    {
        return QString();
    }
    LPTSTR msg;
    DWORD size = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM
        | FORMAT_MESSAGE_ARGUMENT_ARRAY,
        NULL, error, LANG_NEUTRAL, (LPTSTR)&msg, 0, NULL );
    return QString::fromUtf8(msg, size);
}

QList<HWND> snapshotWindows()
{
    snapshotHwnd.clear();
    auto callback = [](HWND hwnd, LPARAM lparam) -> BOOL { snapshotHwnd << hwnd; return 1; };
    EnumWindows(callback, 0);
    return snapshotHwnd;
}

void setWindowLong(HWND hwnd, int index, LONG value)
{
    SetLastError(ERROR_SUCCESS);
    SetWindowLong(hwnd, index, value);
    if (GetLastError() == ERROR_SUCCESS)
    {
        SetWindowPos(hwnd, hwnd, 0, 0, 0, 0,  SWP_NOMOVE | SWP_NOSIZE
            | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE);
    }
}

}
