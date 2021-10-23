#include "RTTI.h"

const RTTI::CClassId& RTTI::CDynamicType::id() noexcept
{
    static const RTTI::CClassId id("CCDynamicType");
    return id;
}