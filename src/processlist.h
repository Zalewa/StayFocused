#ifndef id00c7e8d5_708b_477e_9871_59a1ac261137
#define id00c7e8d5_708b_477e_9871_59a1ac261137

#include <QList>
#include <QString>
#include <windows.h>

struct ProcessEntry
{
    qint64 pid;
    QString exeName;
    QString exePath;

    ProcessEntry()
    {
        pid = 0;
    }
};

struct WindowEntry
{
    qint64 pid;
    HWND hwnd;
    QString error;
    QString text;

    WindowEntry();
    bool isValid() const;
};

class ProcessList
{
public:
    ProcessList();
    ~ProcessList();

    QString error() const;
    QList<ProcessEntry> listProcesses() const;
    QList<WindowEntry> listWindows(qint64 pidFilter = -1) const;

private:
    class PrivData;
    PrivData *d;
};

#endif
