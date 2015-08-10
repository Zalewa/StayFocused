#ifndef id830d0886_5053_4229_8cf0_ef863e0611f1
#define id830d0886_5053_4229_8cf0_ef863e0611f1

#include <QCheckBox>
#include <QMap>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>


class FlagsPanelSignal : public QObject
{
    Q_OBJECT;

public:
    FlagsPanelSignal(QObject *parent)
        : QObject(parent)
    {}

signals:
    void changed();
};


template <class T>
class FlagsPanel : public QWidget
{
public:
    FlagsPanelSignal *signal;

    FlagsPanel(const QMap<T, QString> &names, QWidget *parent)
    {
        this->signal = new FlagsPanelSignal(this);
        auto *layout = new QVBoxLayout(this);

        foreach (T key, names.keys())
        {
            QCheckBox *checkBox = new QCheckBox(names[key], this);
            checkBox->setProperty("flag", key);
            signal->connect(checkBox, SIGNAL(clicked()), SIGNAL(changed()));
            layout->addWidget(checkBox);
        }
    }
    ~FlagsPanel() {}

    T flags() const
    {
        T result = 0;
        QList<QCheckBox *> boxes = findChildren<QCheckBox *>();
        foreach (auto box, boxes)
        {
            if (box->isChecked())
            {
                result |= box->property("flag").value<T>();
            }
        }
        return result;
    }

    void setFlags(T flags)
    {
        QList<QCheckBox *> boxes = findChildren<QCheckBox *>();
        foreach (auto box, boxes)
        {
            T flag = box->property("flag").value<T>();
            box->setChecked((flag & flags) == flag);
        }
    }
};

#endif
