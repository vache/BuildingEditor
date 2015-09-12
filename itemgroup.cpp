#include "itemgroup.h"

ItemGroup::ItemGroup() : _id(""), _chance(0), _area(QRect())
{
}

ItemGroup::ItemGroup(QString id, int chance, QRect area) : _id(id), _chance(chance), _area(area)
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
