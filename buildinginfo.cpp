#include "buildinginfo.h"
#include <stddef.h>

BuildingInfo* BuildingInfo::BuildingInfoInstance = NULL;

BuildingInfo::BuildingInfo()
{
}

BuildingInfo* BuildingInfo::GetBuildingInfo()
{
    if(BuildingInfoInstance == NULL)
    {
        BuildingInfoInstance = new BuildingInfo();
    }

    return BuildingInfoInstance;
}
