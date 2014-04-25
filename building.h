#ifndef BUILDING_H
#define BUILDING_H

#include "buildingmodel.h"

class Building
{
public:
    Building(int dimension);

    BuildingModel* _model;
};

#endif // BUILDING_H
