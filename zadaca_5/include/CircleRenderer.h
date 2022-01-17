#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Shader.h"

void InitCircleRendering(int in_vertexCountPerCicle);

void RenderCircle(glm::vec2 position, float scale);
