#define _CRT_SECURE_NO_WARNINGS

#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <limits>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <CircleRenderer.h>
#include <LineRenderer.h>

class BezierCurve
{
	public:
        glm::vec2 P0;
        glm::vec2 P1;
        glm::vec2 P2;
        glm::vec2 P3;

        static inline auto b0 = [](float const t){ return (1 - t) * (1 - t) * (1 - t); };
        static inline auto b1 = [](float const t){ return 3 * t * (1 - t) * (1 - t);   };
        static inline auto b2 = [](float const t){ return 3 * t * t * (1 - t);         };
        static inline auto b3 = [](float const t){ return t * t * t;                   };

        BezierCurve(
    		glm::vec2 const P0,
    		glm::vec2 const P1,
    		glm::vec2 const P2,
    		glm::vec2 const P3)
    		: P0{ P0 }
    		, P1{ P1 }
    		, P2{ P2 }
    		, P3{ P3 }
    	{}

        std::vector<glm::vec2> GetCurve(
        	int const granularity)
        const noexcept
        {
            auto points = std::vector<glm::vec2>(granularity + 1);

            for (float t = 0; t <= 1; t += 1.f / granularity)
            {
            	points.push_back(Interpolate(t));
            }

            return std::move(points);
        }

        glm::vec2 Interpolate(
        	float const t)
        const noexcept
        {
        	return b0(t) * P0 + b1(t) * P1 + b2(t) * P2 + b3(t) * P3;
        }
};

int main ()
{
	if (!glfwInit())
    {
		std::cout << "Error : could not initilize GLFW";
    }
    
	int width = 1000;
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	GLFWwindow* window = glfwCreateWindow(width, width * 9.f/16.f, "Hello World", NULL, NULL);
	if (!window)
	{
		std::cout << "Error : could not create window";
		glfwTerminate();
	}
    
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cout << "Error : could not initilize Glad";

	glfwSwapInterval(1);

	InitCircleRendering(32);
	InitLineRendering();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    auto const curve = BezierCurve({100, 100}, {100, 500}, {900, 100}, {900, 500});
    auto points = curve.GetCurve(1024);

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        RenderLine(points);
        RenderCircle(curve.P0, 5);
        RenderCircle(curve.P1, 5);
        RenderCircle(curve.P2, 5);
        RenderCircle(curve.P3, 5);
    }

    glfwTerminate();
}
