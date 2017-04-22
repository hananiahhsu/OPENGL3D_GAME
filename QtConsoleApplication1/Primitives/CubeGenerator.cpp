#include "Primitives\CubeGenerator.h"
#include "Primitives\Vertex.h"
#include <glm\glm.hpp>

#define NUM_ARRAY_ELEMENTS(a) sizeof(a)/sizeof(*a)
ShapeData CubeGenerator::MakeCubes()
{
	ShapeData ret_val;
	Vertex cube_vertex[] =
	{
		glm::vec3(-1.0f,1.0f,1.0f),//0
		glm::vec3(1.0f,0.0f,0.0f),//color

		glm::vec3(1.0f,1.0f,1.0f),//1
		glm::vec3(0.0f,1.0f,0.0f),//color

		glm::vec3(1.0f,1.0f,-1.0f),//2
		glm::vec3(0.0f,0.0f,1.0f),//color

		glm::vec3(-1.0f,1.0f,-1.0f),//3
		glm::vec3(1.0f,1.0f,1.0f),//color

		glm::vec3(-1.0f,1.0f,-1.0f),//4
		glm::vec3(1.0f,0.0f,1.0f),//color

		glm::vec3(1.0f,1.0f,-1.0f),//5
		glm::vec3(0.0f,0.5f,0.2f),//color

		glm::vec3(1.0f,-1.0f,-1.0f),//6
		glm::vec3(0.8f,0.6f,0.4f),//color

		glm::vec3(-1.0f,-1.0f,-1.0f),//7
		glm::vec3(0.3f,1.0f,0.5f),//color

		glm::vec3(1.0f,1.0f,-1.0f),//8
		glm::vec3(0.2f,0.5f,0.2f),//color

		glm::vec3(1.0f,1.0f,1.0f),//9
		glm::vec3(0.9f,0.3f,0.7f),//color

		glm::vec3(1.0f,-1.0f,1.0f),//10
		glm::vec3(0.3f,0.7f,0.5f),//color

		glm::vec3(1.0f,-1.0f,-1.0f),//11
		glm::vec3(0.5f,0.7f,0.5f),//color

		glm::vec3(-1.0f,1.0f,1.0f),//12
		glm::vec3(0.7f,0.8f,0.2f),//color

		glm::vec3(-1.0f,1.0f,-1.0f),//13
		glm::vec3(0.5f,0.7f,3.0f),//color

		glm::vec3(-1.0f,-1.0f,-1.0f),//14
		glm::vec3(0.4f,0.7f,0.7f),//color

		glm::vec3(-1.0f,-1.0f,1.0f),//15
		glm::vec3(0.2f,0.5f,1.0f),//color

		glm::vec3(1.0f,1.0f,1.0f),//16
		glm::vec3(0.6f,1.0f,0.7f),//color

		glm::vec3(-1.0f,1.0f,1.0f),//17
		glm::vec3(0.6f,0.4f,0.8f),//color

		glm::vec3(-1.0f,-1.0f,1.0f),//18
		glm::vec3(0.2f,0.8f,0.7f),//color

		glm::vec3(1.0f,-1.0f,1.0f),//19
		glm::vec3(0.2f,0.7f,1.0f),//color

		glm::vec3(1.0f,-1.0f,-1.0f),//20
		glm::vec3(0.8f,0.3f,0.7f),//color

		glm::vec3(-1.0f,-1.0f,-1.0f),//21
		glm::vec3(0.8f,0.9f,0.5f),//color

		glm::vec3(-1.0f,-1.0f,1.0f),//22
		glm::vec3(0.5f,0.8f,0.5f),//color

		glm::vec3(1.0f,-1.0f,1.0f),//23
		glm::vec3(0.9f,1.0f,0.2f),//color
	};

	ret_val.num_vertices = NUM_ARRAY_ELEMENTS(cube_vertex);
	ret_val.vertices = new Vertex[ret_val.num_vertices];
	memcpy(ret_val.vertices, cube_vertex, sizeof(cube_vertex));

	unsigned short indices[] = 
	{ 
		//use 2 triangle to form 1 rectangle,so it's 6 vertices here
		0, 1, 2,  0, 2, 3,//top
		4, 5, 6,  4, 6, 7,//front
		8, 9, 10, 8, 10,11,//right
		12,13,14, 12,14,15,//left
		16,17,18, 16,18,19,//back
		20,22,21, 20,23,22,//bottom
	}; 

	ret_val.num_indices = NUM_ARRAY_ELEMENTS(indices);
	ret_val.indices = new GLushort[ret_val.num_indices];
	memcpy(ret_val.indices, indices, sizeof(indices));

	return ret_val;
}





