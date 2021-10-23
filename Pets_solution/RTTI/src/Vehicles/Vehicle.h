#pragma once
#include "../RTTI/RTTI.h"

class CVehicle : public RTTI::CDynamicType
{
public:
    CVehicle(const std::string& vehicleTypeName)
        :mVehicleTypeName(vehicleTypeName) {}

    virtual ~CVehicle() {}

    DERIVED_FROM(RTTI::CDynamicType);

protected:
    const std::string& getVehicleTypeName() const noexcept  { return mVehicleTypeName; }
    virtual const std::string& getBrandName() const noexcept = 0;

private:
    std::string mVehicleTypeName;
};