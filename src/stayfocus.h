#ifndef id0a306db7_268e_45d4_9fe8_1a8e818f70ab
#define id0a306db7_268e_45d4_9fe8_1a8e818f70ab

#include <QObject>
#include <windows.h>

class MainWindow;
struct WindowEntry;

class StayFocus : public QObject
{
    Q_OBJECT;

public:
    StayFocus(QObject *parent = 0);
    ~StayFocus();

    void addIgnore(HWND ignore);
    void clearIgnore();
    QString error() const;
    bool isFocusing() const;
    void startFocus(HWND window);
    void stopFocus();

signals:
    void focusingChanged(bool focusing);

private:
    class PrivData;
    PrivData *d;

    void attachRemoteThreads(const QList<DWORD> &threads, bool attach);
    QList<DWORD> listWindowsThreads();

private slots:
    void focus();
};

#endif
