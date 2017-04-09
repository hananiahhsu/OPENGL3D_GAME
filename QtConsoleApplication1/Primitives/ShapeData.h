#pragma once
#include <GL\glew.h>
#include "Vertex.h"
//declaration of class Vertex
class Vertex;

struct ShapeData
{
	ShapeData()
		:vertices(0),num_vertices(0),indices(0),num_indices(0)
	{

	}
	Vertex   * vertices;
	GLuint   num_vertices;
	GLushort *indices;
	GLuint   num_indices;
	GLsizeiptr vertexBufferSize()const
	{
		return num_vertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return num_indices * sizeof(GLushort);
	}
};