#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include <QRect>
#include <QString>
#include <QMetaType>

class ItemGroup
{
public:
    ItemGroup();
    ItemGroup(QString id, int chance = 0, QRect area = QRect());

    inline QString GetID() const { return _id; }

    inline void SetChance(int chance) { _chance = chance; }
    inline int GetChance() const { return _chance; }

    inline void SetArea(QRect area) { _area = area; }
    inline QRect GetArea() const { return _area; }

    bool operator==(const ItemGroup & other) const;
    bool operator!=(const ItemGroup & other) const;
//    ItemGroup& operator =(const ItemGroup & other);

private:
    QString _id;
    int _chance;
    QRect _area;
};

Q_DECLARE_METATYPE(ItemGroup)

#endif // ITEMGROUP_H
