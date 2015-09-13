#ifndef MONSTERGROUP_H
#define MONSTERGROUP_H

#include <QRect>
#include <QString>
#include <QMetaType>

class MonsterGroup
{
public:
    MonsterGroup();
    MonsterGroup(QString id, int chance = 0, float density = 0);
    bool operator==(const MonsterGroup & other) const;

    inline QString GetID() const { return _id; }

    // NOTE: chance is implemented in game as 1/chance.
    inline int GetChance() const { return _chance; }
    inline void SetChance(int chance) { _chance = chance; }

    inline float GetDensity() const { return _density; }
    inline void SetDensity(float density) { _density = density; }

// These fields aren't needed for display, but the OMT will need to know them at export time, and
// it keeps me from having to create extra classes just to hold them
private:
    QString _id;
    // Tile will have to know this
    int _chance;
    float _density;
};

Q_DECLARE_METATYPE(MonsterGroup)

#endif // MONSTERGROUP_H
