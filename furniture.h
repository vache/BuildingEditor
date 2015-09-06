#ifndef FURNITURE_H
#define FURNITURE_H

#include "drawableitem.h"

class Furniture : public DrawableItem
{
public:
    Furniture();
    Furniture(QString id, QString desc, QChar sym, nc_color color = nc_color());

};

Q_DECLARE_METATYPE(Furniture)

#endif // FURNITURE_H
