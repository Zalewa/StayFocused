#include "showbox.h"

#include "ui_showbox.h"
#include "window.h"

class ShowBox::PrivData : public Ui::ShowBox
{
public:
    bool applyImmediately;
    HWND hwnd;
    bool loadingSize;
};


ShowBox::ShowBox(QWidget *parent)
    : QWidget(parent)
{
    d = new PrivData();
    d->setupUi(this);
    d->applyImmediately = true;
    d->loadingSize = false;
}

ShowBox::~ShowBox()
{
    delete d;
}

void ShowBox::reload()
{
    if (!isEditing())
    {
        loadSize();
    }
    loadTopmost();
}

bool ShowBox::isEditing() const
{
    if (!isActiveWindow())
    {
        return false;
    }
    QList<QWidget*> editors;
    foreach (auto box, findChildren<QSpinBox*>())
    {
        editors << box;
    }
    return editors.contains(focusWidget());
}

void ShowBox::loadSize()
{
    d->loadingSize = true;
    Window window(d->hwnd);
    QRect rect = window.rect();
    d->spinX->setValue(rect.x());
    d->spinY->setValue(rect.y());
    d->spinWidth->setValue(rect.width());
    d->spinHeight->setValue(rect.height());
    d->loadingSize = false;
}

void ShowBox::loadTopmost()
{
    Window window(d->hwnd);
    bool topmost = window.exStyle().isSet(WS_EX_TOPMOST);

    d->rbKeepOnTop->blockSignals(true);
    d->rbDontKeepOnTop->blockSignals(true);

    d->rbKeepOnTop->setChecked(topmost);
    d->rbDontKeepOnTop->setChecked(!topmost);

    d->rbKeepOnTop->blockSignals(false);
    d->rbDontKeepOnTop->blockSignals(false);
}

void ShowBox::setApplyImmediately(bool b)
{
    d->applyImmediately = b;
}

void ShowBox::setHwnd(HWND hwnd)
{
    d->hwnd = hwnd;
    reload();
}

void ShowBox::minimizeTarget()
{
    Window window(d->hwnd);
    window.minimize();
    emit activated();
}

void ShowBox::maximizeTarget()
{
    Window window(d->hwnd);
    window.maximize();
    emit activated();
}

void ShowBox::showNormalTarget()
{
    Window window(d->hwnd);
    window.showNormal();
    emit activated();
}

void ShowBox::apply()
{
    applyPositionTarget();
    applyTopmost();
}

void ShowBox::applyPositionTarget()
{
    Window window(d->hwnd);
    window.setRect(d->spinX->value(), d->spinY->value(),
        d->spinWidth->value(), d->spinHeight->value());
}

void ShowBox::applyTopmost()
{
    Window window(d->hwnd);
    window.setTopmost(d->rbKeepOnTop->isChecked());
}

void ShowBox::updatePositionTarget()
{
    if (d->applyImmediately && !d->loadingSize)
    {
        applyPositionTarget();
        emit activated();
    }
}

void ShowBox::updateTopmost()
{
    if (d->applyImmediately)
    {
        applyTopmost();
        emit activated();
    }
}
