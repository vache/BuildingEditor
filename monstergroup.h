#ifndef MONSTERGROUP_H
#define MONSTERGROUP_H

#include "highlightableitem.h"
#include <QRect>

class MonsterGroup : public HighlightableItem
{
public:
    MonsterGroup(QString id = "");
    bool operator==(const MonsterGroup & other) const;

    inline int GetChance() const { return _chance; }
    inline void SetChance(int chance) { _chance = chance; }
    inline QRect GetArea() const { return _area; }
    inline void SetArea(QRect area) { _area = area; }

// These fields aren't needed for display, but the OMT will need to know them at export time, and
// it keeps me from having to create extra classes just to hold them
private:
    // Tile will have to know this
    int _chance;
    float _density;
    // OMT will have to know this
    QRect _area;
};

#endif // MONSTERGROUP_H
