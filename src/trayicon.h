#ifndef id40a8add0_20d8_4b15_b015_714256681eeb
#define id40a8add0_20d8_4b15_b015_714256681eeb

#include <QObject>

class MainWindow;

class TrayIcon : public QObject
{
    Q_OBJECT;

public:
    TrayIcon(MainWindow *parent);
    ~TrayIcon();

    void setFocusingIcon();
    void setIdleIcon();

private:
    class PrivData;
    PrivData *d;

private slots:
    void setFocusingIcon(bool focusing);
};

#endif
