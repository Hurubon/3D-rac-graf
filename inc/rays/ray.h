#ifndef RAY_H
#define RAY_H

#include <linear_algebra.h>

struct Ray
{
    float3 source    {};
    float3 direction {};
};

[[nodiscard]]
constexpr float3 reflect(
    float3 const direction,
    float3 const normal)
{
    return direction - 2 * direction.dot(normal) * normal;
}

#endif // RAY_H
