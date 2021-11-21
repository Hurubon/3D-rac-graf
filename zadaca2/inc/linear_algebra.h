#ifndef LINEAR_ALGEBRA_H
#define LINEAR_ALGEBRA_H

#include <cassert>
#include <cmath>

struct float2
{
    float x{};
    float y{};

    [[nodiscard]]
    constexpr float2 operator+(float2 const rhs) const noexcept
    {
        return {x + rhs.x, y + rhs.y,};
    }

    [[nodiscard]]
    constexpr float2 operator-(float2 const rhs) const noexcept
    {
        return {x - rhs.x, y - rhs.y,};
    }

    [[nodiscard]]
    constexpr friend float2 operator*(float const a, float2 const v) noexcept
    {
        return {a * v.x, a * v.y,};
    }

    constexpr float2& operator+=(float2 const rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr float2& operator-=(float2 const rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    [[nodiscard]]
    constexpr float length() const noexcept
    {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]]
    constexpr float2 normalize() const noexcept
    {
        assert(length() != 0);

        return {x / length(), y / length(),};
    }

    [[nodiscard]]
    constexpr float dot(float2 const rhs) const noexcept
    {
        return x * rhs.x + y * rhs.y;
    }
};

struct float3
{
    float x {};
    float y {};
    float z {};

    [[nodiscard]]
    constexpr float3 operator+(float3 const rhs) const noexcept
    {
        return {x + rhs.x, y + rhs.y, z + rhs.z,};
    }

    [[nodiscard]]
    constexpr float3 operator-(float3 const rhs) const noexcept
    {
        return {x - rhs.x, y - rhs.y, z - rhs.z,};
    }

    [[nodiscard]]
    constexpr friend float3 operator*(float const a, float3 const v) noexcept
    {
        return {a * v.x, a * v.y, a * v.z};
    }

    constexpr float3& operator+=(float3 const rhs) noexcept
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    constexpr float3& operator-=(float3 const rhs) noexcept
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    [[nodiscard]]
    constexpr float length() const noexcept
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    [[nodiscard]]
    constexpr float3 normalize() const noexcept
    {
        assert(length() != 0);

        return {x / length(), y / length(), z / length(),};
    }

    [[nodiscard]]
    constexpr float dot(float3 const other) const noexcept
    {
        return x * other.x + y * other.y + z * other.z;
    }

    [[nodiscard]]
    constexpr float3 cross(float3 const rhs) const noexcept
    {
        return {
            .x = y * rhs.z - z * rhs.y,
            .y = z * rhs.x - x * rhs.z,
            .z = x * rhs.y - y * rhs.z,
        };
    }
};

#endif // LINEAR_ALGEBRA_H
