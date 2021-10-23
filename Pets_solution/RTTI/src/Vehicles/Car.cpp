#include "Car.h"
const RTTI::CClassId& CCar::id() noexcept
{
    static const RTTI::CClassId id("CCar");
    return id;
}