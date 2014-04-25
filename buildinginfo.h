#ifndef BUILDINGINFO_H
#define BUILDINGINFO_H

class BuildingInfo
{
public:
    static BuildingInfo* GetBuildingInfo();

private:
    BuildingInfo();
    BuildingInfo(BuildingInfo&){}
    BuildingInfo& operator=(BuildingInfo&){}

    static BuildingInfo* BuildingInfoInstance;
};

#endif // BUILDINGINFO_H
