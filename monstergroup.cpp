#include "monstergroup.h"

MonsterGroup::MonsterGroup(QString id) : HighlightableItem(id, Qt::red), _chance(0), _density(0),
    _area(0,0,0,0)
{
}

bool MonsterGroup::operator ==(const MonsterGroup & other) const
{
    return (_id == other._id) && (_chance == other._chance) && (_density == other._density);
}
