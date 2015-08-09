#include "version.h"

#include "versiondefs.h"

class Version::PrivData
{
public:
};


Version::Version()
{
    d = new PrivData();
}

Version::~Version()
{
    delete d;
}

QString Version::name() const
{
    return tr("Stay Focused!");
}

QString Version::version() const
{
    return VERSION_STRING;
}

QString Version::yearSpan() const
{
    return tr("2015");
}
