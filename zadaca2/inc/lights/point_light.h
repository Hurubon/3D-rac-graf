#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include <linear_algebra.h>

struct PointLight
{
    float3 position{};
    float intensity{};
};

#endif // POINT_LIGHT_H
