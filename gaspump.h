#ifndef GASPUMP_H
#define GASPUMP_H

#include <QString>
#include <QMetaType>

class GasPump
{
public:
    GasPump();
    GasPump(QString fuel, int minAmount=0, int maxAmount=0);

    inline QString GetFuel() const { return _fuel; }
    inline void SetFuel(QString fuel) { _fuel = fuel; }

    inline int GetMinAmount() const { return _minAmount; }
    inline void SetMinAmount(int minAmount) { _minAmount = minAmount; }

    inline int GetMaxAmount() const { return _maxAmount; }
    inline void SetMaxAmount(int maxAmount) { _maxAmount = maxAmount; }

private:
    QString _fuel;
    int _minAmount;
    int _maxAmount;
};

Q_DECLARE_METATYPE(GasPump)

#endif // GASPUMP_H
