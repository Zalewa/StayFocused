#ifndef id74ad6544_e2cf_4cd7_b660_96fc113d6868
#define id74ad6544_e2cf_4cd7_b660_96fc113d6868

#include <QWidget>
#include <windows.h>

class ShowBox : public QWidget
{
    Q_OBJECT;

public:
    ShowBox(QWidget *parent);
    ~ShowBox();

    void reload();
    void setApplyImmediately(bool);
    void setHwnd(HWND hwnd);

public slots:
    void apply();

signals:
    void activated();

private:
    class PrivData;
    PrivData *d;

    void applyPositionTarget();
    void applyTopmost();
    bool isEditing() const;
    void loadSize();

private slots:
    void loadTopmost();
    void minimizeTarget();
    void maximizeTarget();
    void showNormalTarget();
    void updatePositionTarget();
    void updateTopmost();
};

#endif
