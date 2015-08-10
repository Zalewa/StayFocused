#ifndef id390ce9f2_aac4_4a9c_bf94_03158d72dca7
#define id390ce9f2_aac4_4a9c_bf94_03158d72dca7

#include <QMap>
#include <QObject>
#include <QString>
#include <winapi.h>

namespace Def
{

class StyleDef : public QObject
{
    Q_OBJECT;

public:
    static const QMap<LONG, QString> &defs();
};

}

#endif
