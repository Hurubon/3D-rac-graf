#ifndef RAYS_SHADING_H
#define RAYS_SHADING_H

#include <limits>
#include <algorithm>

#include <linear_algebra.h>
#include <objects/object.h>
#include <lights/point_light.h>

[[nodiscard]]
constexpr float3 color_clamp(float3 const color)
{
    return {
        .x = std::min(255.f, color.x),
        .y = std::min(255.f, color.y),
        .z = std::min(255.f, color.z),
    };
}

[[nodiscard]]
constexpr float lambert_model(
    PointLight const light,
    float3     const light_direction,
    float3     const normal)
{
    return light.intensity * std::max(0.f, light_direction.dot(normal));
}

[[nodiscard]]
constexpr float blinn_phong_model(
    PointLight                  const  light,
    float3                      const  light_direction,
    Ray                         const  ray,
    Object::RayIntersectionData const& data)
{
    float3 const view_direction
        = (ray.source - data.intersection_point).normalize();
    float3 const half_vector
        = (light_direction + view_direction).normalize();

    float const reflection_intensity
        = std::max(0.f, half_vector.dot(data.intersection_normal));
    float const exponent
        = data.intersected_object->material.specular_exponent;

    return light.intensity * std::pow(reflection_intensity, exponent);
}

[[nodiscard]]
float3 shade(
    Ray                         const ray,
    Object::RayIntersectionData const data,
    std::vector<Object const*> const& objects,
    std::vector<PointLight   > const& lights)
{
    float diffuse_intensity  = 0;
    float specular_intensity = 0;

    for (auto const light : lights)
    {
        float3 const p = data.intersection_point;
        float3 const n = data.intersection_normal;

        auto const light_direction = (light.position - p).normalize();
        auto const light_distance  = (light.position - p).length();

        float3 shadow_origin;
        if (light_direction.dot(n) < 0)
            shadow_origin = p - 0.001 * n;
        else
            shadow_origin = p + 0.001 * n;

        {
            auto const shadow_data = get_nearest_ray_intersection_data(
                Ray{shadow_origin, light_direction},
                objects
            );
            // Vector from the shadow origin to the blocking object.
            float3 const u = shadow_data.intersection_point - shadow_origin;

            if (shadow_data.intersected_object and u.length() < light_distance)
                continue;
        }

        diffuse_intensity  += lambert_model(light, light_direction, n);
        specular_intensity += blinn_phong_model(light, light_direction, ray, data);
    }

    Material const material = data.intersected_object->material;
    float const d = material.diffuse_coefficient;
    float const s = material.specular_coefficient;

    float3 const diffuse_part  = diffuse_intensity  * d * material.diffuse_color;
    float3 const specular_part = specular_intensity * s * float3{255, 255, 255};

    return color_clamp(diffuse_part + specular_part);
}

#endif // RAYS_SHADING_H
