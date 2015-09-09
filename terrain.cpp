#include "terrain.h"

Terrain::Terrain() : DrawableItem("t_null", "invalid", ' ', nc_color())
{
}

Terrain::Terrain(QString id, QString desc, QChar sym, nc_color(color)) :
    DrawableItem(id, desc, sym, color)
{
}
