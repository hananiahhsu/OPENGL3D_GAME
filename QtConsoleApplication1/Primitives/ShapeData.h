#pragma once
#include <glew.h>
#include "Primitives\Vertex.h"

//declaration of class Vertex
//class Vertex;

class ShapeData
{
public:
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
	void UsrClearShapeData()
	{
		delete[] vertices;
		delete[] indices;
		num_indices = num_vertices = 0;
	}
};