#ifndef CURRENTFEATURE_H
#define CURRENTFEATURE_H

#include <QVariant>
#include "drawableitem.h"
#include "monstergroup.h"
#include "itemgroup.h"

// this class is supposed to be a singleton containing a reference to the current selected feature
// including all of its settings.
class CurrentFeature
{
public:
    static CurrentFeature& Get();

    QVariant Current() { return _current; }
    void SetCurrent(QVariant v) { _current = v; }

    MonsterGroup& MG() { return _mg; }
    ItemGroup& IG() { return _ig; }
    Terrain& T() { return _t; }
    Furniture& F() { return _f; }
    Trap& Tr() { return _tr; }

    void MG(MonsterGroup mg) { _mg = mg; }
    void IG(ItemGroup ig) { _ig = ig; }
    void T(Terrain t) { _t = t; }
    void F(Furniture f) { _f = f; }
    void Tr(Trap tr) { _tr = tr; }

private:
    CurrentFeature();

    MonsterGroup _mg;
    ItemGroup _ig;
    Terrain _t;
    Furniture _f;
    Trap _tr;

    QVariant _current;

    CurrentFeature(CurrentFeature const &) = delete;
    void operator=(CurrentFeature const &) = delete;
};

#endif // CURRENTFEATURE_H
