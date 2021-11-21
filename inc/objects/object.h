#ifndef OBJECT_H
#define OBJECT_H

#include <linear_algebra.h>
#include <rays/ray.h>

struct Material
{
    float3 diffuse_color       {};
    float diffuse_coefficient  {};
    float specular_coefficient {};
    float specular_exponent    {};
};

struct Object
{
    struct RayIntersectionData
    {
        Object const* intersected_object {};
        float  intersection_distance     {};
        float3 intersection_point        {};
        float3 intersection_normal       {};
    };

    Material material {};

    virtual RayIntersectionData get_ray_intersection_data(Ray    const ray  ) const = 0;
    virtual float3              normal                   (float3 const point) const = 0;
};

[[nodiscard]]
Object::RayIntersectionData get_nearest_ray_intersection_data(
    Ray                        const  ray,
    std::vector<Object const*> const& objects)
{
    auto nearest_intersection_data = Object::RayIntersectionData
    {
        .intersected_object    = nullptr,
        .intersection_distance = 20000,
        .intersection_point    = {},
        .intersection_normal   = {},
    };

    for (auto const* object : objects)
    {
        auto const data = object->get_ray_intersection_data(ray);
        auto const d    = data.intersection_distance;

        if (0 < d and d < nearest_intersection_data.intersection_distance)
        {
            nearest_intersection_data = data;
        }
    }

    return nearest_intersection_data;
}

#endif // OBJECT_H
