#include "rubble.h"

Rubble::Rubble() : _rubbleType(""), _items(false), _floorType(""), _overwrite(false)
{

}

Rubble::Rubble(QString rubbleType, bool items, QString floorType, bool overwrite)
    : _rubbleType(rubbleType), _items(items), _floorType(floorType), _overwrite(overwrite)
{

}
