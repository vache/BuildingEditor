#ifndef RUBBLE_H
#define RUBBLE_H

#include <QString>
#include <QMetaType>

class Rubble
{
public:
    Rubble();
    Rubble(QString rubbleType, bool items = false, QString floorType = "", bool overwrite = false);

    inline void SetRubbleType(QString rubbleType) { _rubbleType = rubbleType; }
    inline QString GetRubbleType() const { return _rubbleType; }

    inline void SetCreateItems(bool items) { _items = items; }
    inline bool GetCreateItems() const { return _items; }

    inline void SetFloorType(QString floorType) { _floorType = floorType; }
    inline QString GetFloorType() const { return _floorType; }

    inline void SetOverwrite(bool overwrite) { _overwrite = overwrite; }
    inline bool GetOverwrite() const { return _overwrite; }

private:
    QString _rubbleType;
    bool _items;
    QString _floorType;
    bool _overwrite;
};

Q_DECLARE_METATYPE(Rubble)

#endif // RUBBLE_H
