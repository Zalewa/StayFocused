#include "windowflagsbox.h"

#include <QGroupBox>
#include <QPushButton>
#include <QStatusBar>
#include "flagspanel.h"
#include "styledef.h"
#include "windowflags.h"
#include "ui_windowflagsbox.h"

class WindowFlagsBox::PrivData : public Ui::WindowFlagsBox
{
public:
    HWND hwnd;
    bool immediate;
    FlagsPanel<LONG> *styleFlags;
    QStatusBar *statusBar;
};

WindowFlagsBox::WindowFlagsBox(HWND hwnd, QWidget *parent)
    : QDialog(parent)
{
    d = new PrivData();
    d->setupUi(this);
    d->statusBar = new QStatusBar(this);
    d->statusBarLayout->addWidget(d->statusBar);
    d->hwnd = hwnd;

    this->connect(d->buttonBox->button(QDialogButtonBox::Reset), SIGNAL(clicked()), SLOT(reset()));
    this->connect(d->buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(accept()));

    QGroupBox *groupBox = new QGroupBox(tr("WS_ Style"), this);
    groupBox->setLayout(new QVBoxLayout());
    d->styleFlags = new FlagsPanel<LONG>(Def::StyleDef::defs(), d->flagsArea);
    this->connect(d->styleFlags->signal, SIGNAL(changed()), SLOT(applyStyle()));
    groupBox->layout()->addWidget(d->styleFlags);
    d->flagsArea->layout()->addWidget(groupBox);

    setImmediate(d->rbImmediate->isChecked());
    reset();
}

WindowFlagsBox::~WindowFlagsBox()
{
    delete d;
}

void WindowFlagsBox::accept()
{
    applyStyle();
}

void WindowFlagsBox::applyStyle()
{
    WindowFlags flags(d->hwnd);
    flags.setStyle(d->styleFlags->flags());
    applyErrorStatus();
}

void WindowFlagsBox::applyErrorStatus()
{
    int lastError = GetLastError();
    if (lastError == ERROR_SUCCESS)
    {
        d->statusBar->showMessage(tr("Flags changed."), 1000);
    }
    else
    {
        d->statusBar->showMessage(Winapi::errorMessage(lastError));
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
        reset();
    }
}

void WindowFlagsBox::reset()
{
    WindowFlags flags(d->hwnd);
    d->styleFlags->setFlags(flags.style().flags);
}
