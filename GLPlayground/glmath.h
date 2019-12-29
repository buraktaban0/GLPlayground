#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#define vec3zero glm::vec3(0.0, 0.0, 0.0)
#define vec3one glm::vec3(1.0, 1.0, 1.0)

#define vec3up glm::vec3(0.0, 1.0, 0.0)
#define vec3right glm::vec3(1.0, 0.0, 0.0)
#define vec3forward glm::vec3(0.0, 0.0, 1.0)
#define vec3down glm::vec3(0.0, -1.0, 0.0)
#define vec3left glm::vec3(-1.0, 0.0, 0.0)
#define vec3back glm::vec3(0.0, 0.0, -1.0)


#define vec2zero glm::vec2(0.0, 0.0)
#define vec2one glm::vec2(1.0, 1.0)
#define vec2up glm::vec2(0.0, 1.0)
#define vec2down glm::vec2(0.0, -1.0)
#define vec2left glm::vec2(-1.0, 0.0)
#define vec2right glm::vec2(1.0, 0.0)


#define mat4identity glm::mat4(1.0f)