#pragma once

//Typdefs to mask libraries used, so they can be swapped out without ceasing functionality of the engine

#include "glm/glm.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/matrix_transform.hpp"

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Mat4;
typedef glm::mat3 Mat3;
typedef glm::mat2 Mat2;
typedef glm::mat2x2 Mat2x2;
typedef glm::mat2x3 Mat2x3;
typedef glm::mat2x4 Mat2x4;
typedef glm::mat3x2 Mat3x2;
typedef glm::mat3x3 Mat3x3;
typedef glm::mat3x4 Mat3x4;
typedef glm::mat4x2 Mat4x2;
typedef glm::mat4x3 Mat4x3;
typedef glm::mat4x4 Mat4x4;

#define TRANSFORM 0x80
#define MESH 0x40
#define PHYSICS 0x20
#define CAMERA 0x10
#define LIGHT 0x8
