#include "gaspump.h"

GasPump::GasPump() : _fuel(""), _minAmount(0), _maxAmount(0)
{

}

GasPump::GasPump(QString fuel, int minAmount, int maxAmount) : _fuel(fuel), _minAmount(minAmount), _maxAmount(maxAmount)
{

}
