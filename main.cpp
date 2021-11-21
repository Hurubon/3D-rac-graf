
#include <iostream>
#include <cmath>
#include <cstdint>

#include <vector>
#include <fstream>

#include <linear_algebra.h>

#include <objects/object.h>
#include <objects/sphere.h>
#include <objects/cylinder.h>
#include <objects/cuboid.h>

#include <rays/ray.h>
#include <rays/tracing.h>

template <int w, int h> [[nodiscard]]
std::vector<float3> render(
    std::vector<Object const*> const& objects,
    std::vector<PointLight   > const& lights)
{
    auto const half_height = h / 2.f;
    auto const half_width  = w / 2.f;
    auto const half_fov    = 3.1415 / 3;

    std::vector<float3> image(w * h);

    for (int j = 0; j < h; ++j)
    {
        for (int i = 0; i < w; ++i)
        {
            /*
            ** The ray will go through the pixel at
            **
            **      (i - half_width, half_height - j)
            **
            ** in the near plane, because we have to get
            ** from the center of the plane to the top-left
            ** corner.
            */
            Ray const ray
            {
                .source    = {0, 0, 0},
                .direction = float3
                {
                    static_cast<float>(i - half_width),
                    static_cast<float>(half_height - j) - 100,
                    static_cast<float>(-half_width / atan(half_fov))
                }.normalize()
            };

            image[j * w + i] = trace<16>(ray, objects, lights);
        }
    }

    return image;
}

template <int width, int height>
void convert_to_P6(std::vector<float3> const& image)
{
    std::ofstream output("../renders/kugle.ppm", std::ofstream::binary);

    output << "P6"                   << std::endl;
    output << width << ' ' << height << std::endl;
    output << "255"                  << std::endl;

    for (int i = 0; i < width * height; ++i)
    {
        output << static_cast<unsigned char>(image[i].x)
               << static_cast<unsigned char>(image[i].y)
               << static_cast<unsigned char>(image[i].z);
    }
}

int main()
{
    constexpr Material red {
        {255, 24, 24},
        0.6, 0.3, 60
    };
    constexpr Material green {
        {24, 100, 24},
        0.6, 0.3, 60
    };
    constexpr Material blue {
        {24, 24, 100,},
        0.6, 0.3, 60
    };
    constexpr Material white {
        {255, 255, 255},
        0.6, 0.3, 60
    };

    PointLight light1 { {-20, -149, -50}, 1.4 };
    PointLight light2 { {-35,  120, 0}  , 2   };
    PointLight light3 { {150,  180, 20} , 1   };

    constexpr Cuboid floor(
        white,
        {-1000, -200,    0},
        { 1000, -150, -800}
    );
    constexpr Sphere s1(
        green,
        {0, -90, -350},
        60
    );
    constexpr Cylinder v1(
        red,
        {150, -150, -400},
        25, 65
    );
    constexpr Cuboid c1(
        blue,
        {-200, -149, -300},
        {-125,  -76, -375}
    );

    constexpr auto width  = 1920;
    constexpr auto height = 1080;

    auto const image = render<width, height>(
        {&floor, &s1, &v1, &c1},
        {light1, light2, light3}
    );
    convert_to_P6<width, height>(image);
}
