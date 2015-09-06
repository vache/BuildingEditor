#ifndef TERRAIN_H
#define TERRAIN_H

#include "drawableitem.h"
#include <QSet>

// TODO: is this class necessary or can both it and furniture be typedefs of drawableitem???
class Terrain : public DrawableItem
{
public:
    Terrain();
    Terrain(QString id, QString desc, QChar sym, nc_color color = nc_color());

    void AddFlags(QStringList flags);
    bool HasFlag(QString flag);
private:
    QSet<QString> _flags;
};

Q_DECLARE_METATYPE(Terrain)

#endif // TERRAIN_H
