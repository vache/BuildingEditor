#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>
#include <QMetaType>

class Vehicle
{
public:
    Vehicle();
    Vehicle(QString id, QString name="", int chance=0, int status=-1, int dir=0, int fuel=-1);

    inline QString GetID() const { return _id; }

    inline QString GetName() const { return _name; }
    inline void SetName(QString name) { _name = name; }

    inline int GetChance() const { return _chance; }
    inline void SetChance(int chance) { _chance = chance; }

    inline int GetStatus() const { return _status; }
    inline void SetStatus(int status) { _status = status; }

    inline int GetDirection() const { return _dir; }
    inline void SetDirection(int dir) { _dir = dir; }

    inline int GetFuel() const { return _fuel; }
    inline void SetFuel(int fuel) { _fuel = fuel; }

    Vehicle& operator=(const Vehicle & other);

private:
    QString _id;
    QString _name;
    int _chance;
    int _status;
    int _dir;
    int _fuel;
};

Q_DECLARE_METATYPE(Vehicle)

#endif // VEHICLE_H
