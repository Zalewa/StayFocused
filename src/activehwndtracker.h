#ifndef id8d6b3c00_90ea_4d0d_b48f_4337477b2400
#define id8d6b3c00_90ea_4d0d_b48f_4337477b2400

#include <QObject>
#include <windows.h>

namespace ActiveHwndTrackerCallback
{
    void CALLBACK winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
        LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);
}

class ActiveHwndTracker : public QObject
{
public:
    ActiveHwndTracker(QObject *parent = 0);
    ~ActiveHwndTracker();

    QList<HWND> history() const;

private:
    class PrivData;
    PrivData *d;

    void onHook(DWORD event, HWND hwnd, LONG idObject, LONG idChild,
        DWORD dwEventThread, DWORD dwmsEventTime);

    friend void ActiveHwndTrackerCallback::winEventProc(HWINEVENTHOOK hWinEventHook, DWORD event,
        HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime);

private slots:
    void snapshot();
};

#endif
