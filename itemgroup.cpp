#include "itemgroup.h"

ItemGroup::ItemGroup() : _id(""), _chance(0)
{
}

ItemGroup::ItemGroup(QString id, int chance) : _id(id), _chance(chance)
{
}

bool ItemGroup::operator ==(const ItemGroup & other) const
{
    return ((_id == other._id) && (_chance == other._chance));
}

bool ItemGroup::operator !=(const ItemGroup & other) const
{
    return ((_id != other._id) || (_chance != other._chance));
}

//ItemGroup& ItemGroup::operator =(const ItemGroup& other)
//{
//    this->_chance = other._chance;
//    this->_id = other._id;

//    return *this;
//}

uint qHash(ItemGroup ig)
{
    return qHash(ig.GetChance()) + qHash(ig.GetID());
}
