#ifndef ITEMGROUP_H
#define ITEMGROUP_H

#include "highlightableitem.h"

#include <QRect>

class ItemGroup : public HighlightableItem
{
public:
    ItemGroup(QString id = "");

private:
    int _chance;
    QRect _area;
};

#endif // ITEMGROUP_H
