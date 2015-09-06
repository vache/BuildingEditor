#ifndef TRAP_H
#define TRAP_H

#include "drawableitem.h"

class Trap : public DrawableItem
{
public:
    Trap(QString id, QString desc, QChar sym, nc_color color = nc_color());
};

#endif // TRAP_H
