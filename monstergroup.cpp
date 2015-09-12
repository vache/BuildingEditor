#include "monstergroup.h"

MonsterGroup::MonsterGroup() : _id(""), _chance(0), _density(0), _area(QRect())
{
}

MonsterGroup::MonsterGroup(QString id, int chance, float density, QRect area) : _id(id),
    _chance(chance), _density(density), _area(area)
{
}

bool MonsterGroup::operator ==(const MonsterGroup & other) const
{
    return (_id == other._id) && (_chance == other._chance) && (_density == other._density);
}
