#include "ShapeGenerator.h"
#include "Primitives\Vertex.h"
//#include <GL\glew.h>
#include <glm\glm.hpp>
#include <Primitives\Vertex.h>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)
ShapeData ShapeGenerator::MakeTriangles()
{
	ShapeData ret_val;
	Vertex myTri[] =
	{
		glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),

		glm::vec3(-1.0f,-1.0f,0.0f),
		glm::vec3(0.0f,1.0f,0.0f),

		glm::vec3(1.0f,-1.0f,0.0f),
		glm::vec3(0.0f,0.0f,1.0f),
	};

	ret_val.num_vertices = NUM_ARRAY_ELEMENTS(myTri);
	ret_val.vertices = new Vertex[ret_val.num_vertices];
	memcpy(ret_val.vertices,myTri,sizeof(myTri));

	GLushort indices[] = { 0,1,2 };
	ret_val.num_indices = NUM_ARRAY_ELEMENTS(indices);
	ret_val.indices = new GLushort[ret_val.num_indices];
	memcpy(ret_val.indices,indices,sizeof(indices));

	return ret_val;
}

