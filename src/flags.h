#ifndef idf6bd2def_e002_442d_b9fc_80eb48f9ff86
#define idf6bd2def_e002_442d_b9fc_80eb48f9ff86

template <class T>
class Flags
{
public:
    Flags()
    {
        this->flags = 0;
    }

    Flags(T flags)
    {
        this->flags = flags;
    }

    bool isSet(T flags) const
    {
        return (this->flags & flags) == flags;
    }

    void set(T flags, bool set)
    {
        if (set)
        {
            this->flags |= flags;
        }
        else
        {
            this->flags &= ~flags;
        }
    }

    operator T() const
    {
        return this->flags;
    }

    bool operator==(const Flags<T> &other) const
    {
        return this->flags == other.flags;
    }

    bool operator!=(const Flags<T> &other) const
    {
        return this->flags != other.flags;
    }

private:
    T flags;
};

template<class T>
class FlagSet
{
public:
    Flags<T> flags;
    QMap<T, QString> names;

    FlagSet() {}
    FlagSet(const QMap<T, QString> &names)
    {
        this->names = names;
    }

    FlagSet(const QMap<T, QString> &names, Flags<T> flags)
    {
        this->names = names;
        this->flags = flags;
    }

    QString name(T flag) const
    {
        return names[flag];
    }
};

#endif
