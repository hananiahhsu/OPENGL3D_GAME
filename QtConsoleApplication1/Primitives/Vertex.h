#pragma once
#include<glm\glm.hpp>
//vertex structure
struct Vector
{
	float x, y, z;
};

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
};