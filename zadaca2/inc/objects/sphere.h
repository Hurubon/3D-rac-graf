#ifndef SPHERE_H
#define SPHERE_H

#include <linear_algebra.h>
#include <objects/object.h>

struct Sphere final : public Object
{
    float3 center {};
    float  radius {};

    constexpr Sphere(
        Material const mat,
        float3   const center,
        float    const radius)
        : center{center}
        , radius{radius}
    {
        Object::material = mat;
    }

    [[nodiscard]]
    constexpr RayIntersectionData
    get_ray_intersection_data(Ray const ray) const noexcept final
    {
        /*
        ** The ray is defined in terms of vectors as
        **
        **      P(t) = s + td , t > 0
        **
        ** where s is the source and d is the direction.
        ** On the other hand, a sphere is defined as the
        ** locus of points P which satisfy the equation:
        **
        **      (1) ||P - C||^2       = r^2.
        **      (2) (P - C) . (P - C) = r^2
        **      (3) (P - C)^2         = r^2
        **
        ** Substituting the ray, we get:
        **
        **      (s + td - c)^2 = r^2
        ** =>   (td + s - c)^2 = r^2
        **
        ** If we take v = s - c
        */
        float3 const d = ray.direction;
        float3 const v = ray.source - center;
        auto const r = radius;
        /*
        ** and use the binomial theorem, we get:
        **
        **      d^2 * t^2 + 2(d . v) * t + v^2 = r^2
        ** =>   d^2 * t^2 + 2(d . v) * t + v^2 - r^2 = 0
        **
        ** This is a quadratic in t, with coefficients:
        */
        auto const a = d.dot(d);
        auto const b = 2 * d.dot(v);
        auto const c = v.dot(v) - r * r;

        auto const determinant = b*b - 4*a*c;

        if (determinant <= 0)
        {
            /*
            ** Zero or one solution => no intersection or tangent.
            ** Negative values indicate something we don't care about
            ** or can't see.
            */
            return {this, -1};
        }
        else
        {
            auto const t1 = ( -b - std::sqrt(determinant) ) / (2 * a);
            auto const t2 = ( -b + std::sqrt(determinant) ) / (2 * a);
            float t = 0;

            // If both solutions are negative, the sphere is behind us.
            // If only one, we are inside the sphere.
            // If two, the sphere is in front of us.
            if (t1 <= 0)
                t = t2;
            else
                t = t1;

            auto const intersection = ray.source + t * ray.direction;
            return {this, t, intersection, normal(intersection)};
        }
    }

    [[nodiscard]]
    float3 normal(float3 const point) const noexcept final
    {
        return (point - center).normalize();
    }
};

#endif // SPHERE_H
