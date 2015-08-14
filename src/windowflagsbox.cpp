#include "windowflagsbox.h"

#include <QGroupBox>
#include <QPushButton>
#include <QStatusBar>
#include <QTimer>
#include "flagspanel.h"
#include "styledef.h"
#include "window.h"
#include "ui_windowflagsbox.h"

#define BAIL_ON_ERR(a) if (!a) { return false; }

class WindowFlagsBox::PrivData : public Ui::WindowFlagsBox
{
public:
    HWND hwnd;
    bool immediate;
    FlagsPanel<LONG> *styleFlags;
    FlagsPanel<LONG> *exStyleFlags;
    QStatusBar *statusBar;
    QTimer resetTimer;
};

WindowFlagsBox::WindowFlagsBox(HWND hwnd, QWidget *parent)
    : QDialog(parent)
{
    d = new PrivData();
    d->setupUi(this);
    d->statusBar = new QStatusBar(this);
    d->statusBarLayout->addWidget(d->statusBar);
    d->hwnd = hwnd;

    d->resetTimer.setInterval(200);
    this->connect(&d->resetTimer, SIGNAL(timeout()), SLOT(reset()));

    this->connect(d->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()), SLOT(reset()));
    this->connect(d->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(accept()));

    d->styleFlags = new FlagsPanel<LONG>(Def::StyleDef::wsStyles(), d->flagsArea);
    this->connect(d->styleFlags->signal, SIGNAL(changed()), SLOT(applyStyle()));
    addFlagsBox(tr("WS styles"), d->styleFlags);

    d->exStyleFlags = new FlagsPanel<LONG>(Def::StyleDef::wsExStyles(), d->flagsArea);
    this->connect(d->exStyleFlags->signal, SIGNAL(changed()), SLOT(applyExStyle()));
    addFlagsBox(tr("WS ex styles"), d->exStyleFlags);

    setImmediate(d->rbImmediate->isChecked());
    reset();
}

WindowFlagsBox::~WindowFlagsBox()
{
    delete d;
}

void WindowFlagsBox::addFlagsBox(const QString &name, QWidget *box)
{
    QGroupBox *groupBox = new QGroupBox(name, this);
    groupBox->setLayout(new QVBoxLayout());
    groupBox->layout()->addWidget(box);
    d->flagsArea->layout()->addWidget(groupBox);
}

void WindowFlagsBox::accept()
{
    apply();
    reset();
}

bool WindowFlagsBox::apply()
{
    BAIL_ON_ERR(applyStyle());
    BAIL_ON_ERR(applyExStyle());
    return true;
}

bool WindowFlagsBox::applyStyle()
{
    Window window(d->hwnd);
    window.setStyle(d->styleFlags->flags());
    bool ok = applyErrorStatus();
    if (d->immediate)
    {
        reset();
    }
    return ok;
}

bool WindowFlagsBox::applyExStyle()
{
    Window window(d->hwnd);
    window.setExStyle(d->exStyleFlags->flags());
    bool ok = applyErrorStatus();
    if (d->immediate)
    {
        reset();
    }
    return ok;
}

bool WindowFlagsBox::applyErrorStatus()
{
    int lastError = GetLastError();
    if (lastError == ERROR_SUCCESS)
    {
        d->statusBar->showMessage(tr("Flags changed."), 1000);
        return true;
    }
    else
    {
        d->statusBar->showMessage(Winapi::errorMessage(lastError));
        return false;
    }
}

void WindowFlagsBox::setImmediate(bool immediate)
{
    d->immediate = immediate;
    d->buttonBox->button(QDialogButtonBox::Reset)->setVisible(!immediate);
    d->buttonBox->button(QDialogButtonBox::Apply)->setVisible(!immediate);
    d->styleFlags->signal->blockSignals(!immediate);
    if (immediate)
    {
        d->resetTimer.start();
        reset();
    }
    else
    {
        d->resetTimer.stop();
    }
}

void WindowFlagsBox::reset()
{
    Window window(d->hwnd);
    d->styleFlags->setFlags(window.style().flags);
    d->exStyleFlags->setFlags(window.exStyle().flags);
}
