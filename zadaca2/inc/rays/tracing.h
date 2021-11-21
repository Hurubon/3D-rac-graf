#ifndef RAYS_TRACING_H
#define RAYS_TRACING_H

#include <linear_algebra.h>
#include <objects/object.h>
#include <rays/ray.h>
#include <rays/shading.h>

template <int max_depth> [[nodiscard]]
constexpr float3 trace(
    Ray                        const  ray,
    std::vector<Object const*> const& objects,
    std::vector<PointLight   > const& lights,
    int                        const  depth = 0)
{
    if (depth >= max_depth)
        return {0, 0, 0};

    auto const data = get_nearest_ray_intersection_data(ray, objects);

    if (data.intersected_object)
    {
        auto const p = data.intersection_point;
        auto const n = data.intersection_normal;

        Ray const reflected =
        {
            .source    = p + 0.1 * n,
            .direction = reflect(ray.direction, n)
        };

        return color_clamp(
            shade(ray, data, objects, lights)
            + 0.4 * trace<max_depth>(reflected, objects, lights, depth + 1)
        );
    }
    else
    {
        return {0, 0, 0};
    }
}

#endif // RAYS_TRACING_H
