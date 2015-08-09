#ifndef id1ecba6f6_712d_436e_b086_42e2425bd5c3
#define id1ecba6f6_712d_436e_b086_42e2425bd5c3

#include <QMainWindow>

struct ProcessEntry;
struct WindowEntry;

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

signals:
    void focusingChanged(bool focusing);

private:
    class PrivData;
    PrivData *d;

    void showError(const QString &msg);
    void setProcessesBox(const QList<ProcessEntry>&);
    void setWindowsBox(const QList<WindowEntry>&);
    qint64 selectedProcessId() const;
    void* selectedWindowHandle() const;
    void startFocus();

private slots:
    void goToHomePage();
    void loadProcesses();
    void loadWindowHandlesForCurrentProcess();
    void onFocusingChanged(bool focusing);
    void showAbout();
    void stopFocus();
    void toggleFocus();
};

#endif
