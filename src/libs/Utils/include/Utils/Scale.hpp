#pragma once
// SCALE — linear mapping of a value from one range to another.
// Equivalent to the IEC 61131-3 SCALE function block behaviour:
//   out = outMin + (value - inMin) / (inMax - inMin) * (outMax - outMin)
//
// Returns outMin when inMax == inMin to avoid division by zero.

#include "Arp/System/Core/Arp.h"

namespace Utils
{

inline double
Scale(double value, double inMin, double inMax, double outMin, double outMax)
{
    if (inMax == inMin)
        return outMin;

    return outMin + ((value - inMin) / (inMax - inMin)) * (outMax - outMin);
}

} // namespace Utils
