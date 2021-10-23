#pragma once
#include "Vehicle.h"

class CCar : public CVehicle
{
public:
    CCar(const std::string& vehicleTypeName, const std::string& brandName)
        : base(vehicleTypeName)
        , mBrandName(brandName)
    {}
    ~CCar() {}

    DERIVED_FROM(CVehicle);

    virtual const std::string& getBrandName() const noexcept override { return mBrandName; }

private:
    std::string mBrandName;
};
