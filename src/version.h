#ifndef idfd580038_69ca_445f_a2cf_c50adc4569d8
#define idfd580038_69ca_445f_a2cf_c50adc4569d8

#include <QObject>

class Version : public QObject
{
Q_OBJECT

public:
    Version();
    ~Version();

    QString name() const;
    QString version() const;
    QString yearSpan() const;

private:
    class PrivData;
    PrivData *d;
};

#endif
