#ifndef id519740ec_914c_46ef_8bb6_30ec1ff20dd3
#define id519740ec_914c_46ef_8bb6_30ec1ff20dd3

#include <QDialog>
#include <windows.h>

class WindowFlagsBox : public QDialog
{
    Q_OBJECT;

public:
    WindowFlagsBox(HWND hwnd, QWidget *parent);
    ~WindowFlagsBox();

public slots:
    void accept();

private:
    class PrivData;
    PrivData *d;

    void applyErrorStatus();

private slots:
    void applyStyle();
    void setImmediate(bool);
    void reset();
};

#endif
