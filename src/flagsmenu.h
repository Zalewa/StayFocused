#ifndef idebe49408_a29c_4093_8a27_d69661a84d3f
#define idebe49408_a29c_4093_8a27_d69661a84d3f

#include <QMenu>
#include <windows.h>

class FlagsMenu : public QMenu
{
    Q_OBJECT;

public:
    FlagsMenu(HWND hwnd, QWidget *parent);
    ~FlagsMenu();

private:
    class PrivData;
    PrivData *d;

    void setup();
    void setupStyleMenu();

private slots:
    void onStyleActionTriggered(QAction *action);
};

#endif
