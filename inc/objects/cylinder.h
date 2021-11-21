#ifndef CYLINER_H
#define CYLINER_H

#include <linear_algebra.h>
#include <objects/object.h>
#include <rays/ray.h>

struct Cylinder final : public Object
{
    float3 center {};
    float  radius {};
    float  height {};

    constexpr Cylinder(
        Material const mat,
        float3   const center,
        float    const radius,
        float    const height)
        : center{center}
        , radius{radius}
        , height{height}
    {
        Object::material = mat;
    }

    [[nodiscard]]
    constexpr RayIntersectionData
    get_ray_intersection_data(Ray const ray) const noexcept final
    {
        float3 const s = ray.source;
        float3 const d = ray.direction;
        float3 const v = s - center;

        auto const a = d.dot(d) - d.y * d.y;
        auto const b = 2 * (d.dot(v) - d.y * v.y);
        auto const c = v.dot(v) - v.y * v.y - radius * radius;

        float const determinant = b*b - 4*a*c;

        if (determinant <= 0)
        {
            return {this, -1};
        }
        else
        {
            auto const t1 = ( -b - std::sqrt(determinant) ) / (2 * a);
            auto const t2 = ( -b + std::sqrt(determinant) ) / (2 * a);

            auto const intersection1 = ray.source + t1 * ray.direction;
            auto const intersection2 = ray.source + t2 * ray.direction;

            float t = 0;

            if      (intersection1.y >= center.y and t1 > 0 and
                     intersection1.y <= center.y + height)
            {
                return {this, t1, intersection1, normal(intersection1)};
            }
            else if (intersection2.y >= center.y and t2 > 0 and
                     intersection2.y <= center.y + height)
            {
                return {this, t2, intersection2, normal(intersection2)};
            }
            else
            {
                return {this, -1};
            }

        }
    }

    [[nodiscard]]
    constexpr float3 normal(float3 const point) const noexcept final
    {
        // Remove the y component.
        float3 const v = {point.x - center.x, 0, point.z - center.z};

        return v.normalize();
    }
};

#endif // CYLINDER_H
