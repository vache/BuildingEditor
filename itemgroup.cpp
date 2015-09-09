#include "itemgroup.h"

ItemGroup::ItemGroup(QString id) : HighlightableItem(id, Qt::green), _chance(0), _area(0,0,0,0)
{
}
