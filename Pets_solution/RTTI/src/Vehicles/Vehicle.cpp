#include "Vehicle.h"

const RTTI::CClassId& CVehicle::id() noexcept
{
    static const RTTI::CClassId id("CVehicle");
    return id;
}