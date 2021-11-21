#ifndef CUBOID_H
#define CUBOID_H

#include <algorithm>
#include <limits>

#include <linear_algebra.h>
#include <objects/object.h>
#include <rays/ray.h>

struct Cuboid final : public Object
{
    float3 v1;
    float3 v2;

    constexpr Cuboid(
        Material const mat,
        float3   const v1,
        float3   const v2)
        : v1{v1}
        , v2{v2}
    {
        Object::material = mat;
    }

    [[nodiscard]]
    constexpr RayIntersectionData
    get_ray_intersection_data(Ray const ray) const noexcept final
    {
        auto t_near = std::numeric_limits<float>::min();
        auto t_far  = std::numeric_limits<float>::max();

        float3 const min = {
            std::min(v1.x, v2.x), std::min(v1.y, v2.y), std::min(v1.z, v2.z)
        };
        float3 const max = {
            std::max(v1.x, v2.x), std::max(v1.y, v2.y), std::max(v1.z, v2.z)
        };
        float3 const d = ray.direction;
        float3 const s = ray.source;

        float t = 0;

        if (d.x == 0 and (s.x < min.x or s.x > max.x))
        {
            return {this, -1};
        }
        else
        {
            auto t1 = (min.x - s.x) / d.x;
            auto t2 = (max.x - s.x) / d.x;

            if (t1 > t2)
            {
                std::swap(t1, t2);
            }

            t_near = std::max(t_near, t1);
            t_far  = std::min(t_far , t2);

            if (t_near > t_far or t_far <= 0)
                return {this, -1};
        }

        t = t_near;

        if (d.y == 0 and (s.y < min.y or s.y > max.y))
        {
            return {this, -1};
        }
        else
        {
            auto t1 = (min.y - s.y) / d.y;
            auto t2 = (max.y - s.y) / d.y;

            if (t1 > t2)
            {
                std::swap(t1, t2);
            }

            t_near = std::max(t_near, t1);
            t_far  = std::min(t_far , t2);

            if (t_near > t_far or t_far <= 0)
                return {this, -1};
        }

        t = t_near;

        if (d.z == 0 and (s.z < min.z or s.z > max.z))
        {
            return {this, -1};
        }
        else
        {
            auto t1 = (min.z - s.z) / d.z;
            auto t2 = (max.z - s.z) / d.z;

            if (t1 > t2)
            {
                std::swap(t1, t2);
            }

            t_near = std::max(t_near, t1);
            t_far  = std::min(t_far , t2);

            if (t_near > t_far or t_far <= 0)
                return {this, -1};
        }

        t = t_near;

        return {this, t, s + t * d, normal(s + t * d)};
    }

    [[nodiscard]]
    constexpr float3 normal(float3 const point) const noexcept final
    {
        using std::abs;

        if      (abs(point.x - v1.x) < 0.01) return {-1,  0,  0};
        else if (abs(point.x - v2.x) < 0.01) return { 1,  0,  0};
        else if (abs(point.y - v1.y) < 0.01) return { 0, -1,  0};
        else if (abs(point.y - v2.y) < 0.01) return { 0,  1,  0};
        else if (abs(point.z - v1.z) < 0.01) return { 0,  0, -1};
        else if (abs(point.z - v2.z) < 0.01) return { 0,  0,  1};
        else                                 return { 0,  0,  0};
    }
};

#endif // CUBOID_H
