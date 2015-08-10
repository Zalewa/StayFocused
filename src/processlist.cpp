#include "processlist.h"

#include <algorithm>
#include <windows.h>
#include <TlHelp32.h>
#include "winapi.h"
#include <QDebug>

class ProcessList::PrivData
{
public:
    DWORD error;

    ProcessEntry toProcessEntry(PROCESSENTRY32 entry)
    {
        ProcessEntry result;
        result.pid = entry.th32ProcessID;
        result.exeName = QString::fromUtf8(entry.szExeFile);
        return result;
    }
};


ProcessList::ProcessList()
{
    d = new PrivData();
    d->error = 0;
}

ProcessList::~ProcessList()
{
    delete d;
}

QString ProcessList::error() const
{
    return Winapi::errorMessage(d->error);
}

QList<ProcessEntry> ProcessList::listProcesses() const
{
    d->error = ERROR_SUCCESS;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
    {
        d->error = GetLastError();
        return QList<ProcessEntry>();
    }
    QList<ProcessEntry> list;
    PROCESSENTRY32 winEntry;
    winEntry.dwSize = sizeof(PROCESSENTRY32);
    if (Process32First(snapshot, &winEntry))
    {
        list << d->toProcessEntry(winEntry);
        while (Process32Next(snapshot, &winEntry))
        {
            list << d->toProcessEntry(winEntry);
        }
    }
    CloseHandle(snapshot);
    auto comparer = [](const ProcessEntry& a, const ProcessEntry& b) -> bool
        { return a.exeName.toLower() < b.exeName.toLower(); };
    std::sort(list.begin(), list.end(), comparer);
    return list;
}

QList<WindowEntry> ProcessList::listWindows(qint64 pidFilter) const
{
    d->error = ERROR_SUCCESS;
    QList<HWND> handles = Winapi::snapshotWindows();
    QList<WindowEntry> list;
    foreach (auto hwnd, handles)
    {
        WindowEntry entry;
        entry.hwnd = hwnd;
        int textLength = GetWindowTextLength(hwnd);
        if (textLength > 0)
        {
            LPTSTR text = new TCHAR[textLength + 2];
            int length = GetWindowText(hwnd, text, textLength + 1);
            if (length > 0)
            {
                text[length + 1] = '\0';
                entry.text = QString::fromUtf8(text);
            }
            else
            {
                entry.error = Winapi::errorMessage(GetLastError());
            }
            delete [] text;
        }

        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == 0)
        {
            entry.error = Winapi::errorMessage(GetLastError());
        }
        entry.pid = pid;
        if (pidFilter < 0 || entry.pid == pidFilter)
        {
            list << entry;
        }
    }
    return list;
}

qint64 ProcessList::pidForHwnd(HWND hwnd)
{
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid;
}

bool ProcessList::isMyHwnd(HWND hwnd)
{
    return pidForHwnd(hwnd) == GetCurrentProcessId();
}

///////////////////////////////////////////////////////////////////////////
WindowEntry::WindowEntry()
{
    pid = 0;
    hwnd = 0;
}

bool WindowEntry::isValid() const
{
    return hwnd != 0;
}
