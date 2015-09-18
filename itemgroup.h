#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QString>
#include <QMetaType>
#include <QHash>

class ItemGroup
{
public:
    ItemGroup();
    ItemGroup(QString id, int chance = 0);

    inline QString GetID() const { return _id; }

    // NOTE: chance is implemented in game as a %, ie. if (rng(0,99) < chance) { spawn_item }
    inline void SetChance(int chance) { _chance = chance; }
    inline int GetChance() const { return _chance; }

    bool operator==(const ItemGroup & other) const;
    bool operator!=(const ItemGroup & other) const;
//    ItemGroup& operator =(const ItemGroup & other);

private:
    QString _id;
    int _chance;
};

uint qHash(ItemGroup);

static ItemGroup null_item_group("", 0);

Q_DECLARE_METATYPE(ItemGroup)

#endif // ITEMGROUP_H
