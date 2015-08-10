#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "processlist.h"
#include "stayfocus.h"
#include "trayicon.h"
#include "version.h"
#include <windows.h>
#include <TlHelp32.h>
#include <QDebug>
#include <QDesktopServices>
#include <QTimer>
#include <QMessageBox>
#include <QUrl>

class MainWindow::PrivData : public Ui::MainWindow
{
public:
    StayFocus *stayFocus;
    QTimer reloadTimer;
    TrayIcon *trayIcon;
};


MainWindow::MainWindow()
{
    d = new PrivData();
    d->setupUi(this);

    d->trayIcon = new TrayIcon(this);

    menuBar()->addAction(tr("About"), this, SLOT(showAbout()));
    menuBar()->addAction(tr("About Qt"), qApp, SLOT(aboutQt()));
    menuBar()->addAction(tr("Home page"), this, SLOT(goToHomePage()));

    d->stayFocus = new StayFocus(this);
    this->connect(d->stayFocus, SIGNAL(focusingChanged(bool)), SLOT(onFocusingChanged(bool)));

    this->connect(&d->reloadTimer, SIGNAL(timeout()), SLOT(loadProcesses()));
    d->reloadTimer.start(1000);
    loadProcesses();
}

MainWindow::~MainWindow()
{
    delete d;
}

void MainWindow::loadProcesses()
{
    if (d->cboProcesses->view()->isVisible())
    {
        return;
    }
    ProcessList list;
    QList<ProcessEntry> processes = list.listProcesses();
    if (list.error().isNull())
    {
        setProcessesBox(processes);
    }
    else
    {
        showError(list.error());
    }
}

void MainWindow::setProcessesBox(const QList<ProcessEntry> &processes)
{
    qint64 selectedId = selectedProcessId();
    d->cboProcesses->blockSignals(true);
    d->cboProcesses->clear();
    foreach (const auto &entry, processes)
    {
        d->cboProcesses->addItem(tr("%1: %2").arg(entry.pid).arg(entry.exeName), entry.pid);
    }
    int idIndex = d->cboProcesses->findData(selectedId);
    if (idIndex >= 0)
    {
        d->cboProcesses->setCurrentIndex(idIndex);
    }
    else
    {
        d->cboWindows->clear();
        stopFocus();
    }
    d->cboProcesses->blockSignals(false);
}

qint64 MainWindow::selectedProcessId() const
{
    return d->cboProcesses->currentData().toLongLong();
}

void MainWindow::loadWindowHandlesForCurrentProcess()
{
    ProcessList list;
    QList<WindowEntry> windows = list.listWindows(selectedProcessId());
    if (!list.error().isNull())
    {
        showError(list.error());
    }
    setWindowsBox(windows);
}

void MainWindow::setWindowsBox(const QList<WindowEntry>& windows)
{
    d->cboWindows->clear();
    foreach (const auto &window, windows)
    {
        d->cboWindows->addItem(tr("%1: %2").arg(
                (qint64)(window.hwnd), 0, 16).arg(window.text),
            qVariantFromValue<void*>(window.hwnd));
    }
}

void MainWindow::toggleFocus()
{
    statusBar()->clearMessage();
    if (!d->stayFocus->isFocusing())
    {
        startFocus();
    }
    else
    {
        stopFocus();
    }
}

void MainWindow::startFocus()
{
    HWND hwnd = static_cast<HWND>(selectedWindowHandle());
    if (hwnd == 0)
    {
        showError(tr("Select window first."));
    }
    else
    {
        d->stayFocus->clearIgnore();
        d->stayFocus->addIgnore((HWND)winId());
        d->stayFocus->startFocus(hwnd);
        if (!d->stayFocus->error().isNull())
        {
            showError(d->stayFocus->error());
        }
    }
}

void MainWindow::stopFocus()
{
    d->stayFocus->stopFocus();
}

void* MainWindow::selectedWindowHandle() const
{
    return d->cboWindows->currentData().value<void*>();
}

void MainWindow::onFocusingChanged(bool focusing)
{
    QIcon icon;
    if (focusing)
    {
        icon = QIcon(":/icons/activated_64");
        d->btnStayFocus->setText(tr("Stop Focusing"));
        statusBar()->showMessage(tr("Focusing started"), 2000);
        setWindowTitle(tr("Staying Focused!"));
    }
    else
    {
        icon = QIcon(":/icons/icon_64");
        d->btnStayFocus->setText(tr("Stay Focused!"));
        statusBar()->showMessage(tr("Focusing stopped"), 2000);
        if (!d->stayFocus->error().isNull())
        {
            showError(d->stayFocus->error());
        }
        setWindowTitle(tr("Stay Focused!"));
    }
    d->btnStayFocus->setIcon(icon);
    setWindowIcon(icon);
    emit focusingChanged(focusing);
}

void MainWindow::showError(const QString &msg)
{
    statusBar()->showMessage(msg);
}

void MainWindow::goToHomePage()
{
    QDesktopServices::openUrl(QString("https://github.com/Zalewa/StayFocused"));
}

void MainWindow::showAbout()
{
    Version v;
    QString msg = tr("%1 %2 (Zalewa %3)").arg(v.name(), v.version(), v.yearSpan());
    QMessageBox::about(this, tr("About"), msg);
}
