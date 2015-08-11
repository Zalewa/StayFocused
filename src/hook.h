#ifndef id5c652e99_0b4c_4934_934c_d23938cc8c97
#define id5c652e99_0b4c_4934_934c_d23938cc8c97

#include <windows.h>
#include <QObject>

struct HookEvent
{
    DWORD event;
    HWND hwnd;
    LONG idObject;
    LONG idChild;
    DWORD dwEventThread;
    DWORD dwmsEventTime;
};

namespace HookCallback
{
    void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event,
        HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
}

class Hook : public QObject
{
    Q_OBJECT;

public:
    Hook(QObject *parent = 0);
    ~Hook();

    const QString &error() const;

    bool hookEvent(UINT event);
    void unhook();

signals:
    void activated(const HookEvent &event);

private:
    class PrivData;
    PrivData *d;

    void onHook(DWORD event, HWND hwnd, LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    friend void HookCallback::winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event,
        HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
};

#endif
