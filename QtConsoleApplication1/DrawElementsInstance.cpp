#include <glew.h>//put before MeGLWindow.h,or the error taking place
#include <DrawElementsInstance.h>
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\ShapeGenerator.h"
using namespace std;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles1 = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;


void DrawElementsInstance::sendDataToOpenGL()
{
#if 1
	GLfloat tri[] =
	{
		-1.0f,0.0f,
		-1.0f,1.0f,
		-0.9f,0.0f,
	};

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri), tri, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);


	GLfloat offsets[] = {0.0,0.5,1.0,2.0,2.5};
	GLuint offset_buffer_id;
	glGenBuffers(1,&offset_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER,offset_buffer_id);
	glBufferData(GL_ARRAY_BUFFER,sizeof(offsets),offsets,GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,0,0);//if tri data tightly packed, then fill 0 and 0 for the last 2 elements
	glVertexAttribDivisor(1,2);//the divisor could be 2(0/2->0,1/2->1,2/2->1,3/2->1,4/2->2)


	GLushort indices[] = {0,1,2,};
	GLuint index_buffer_id;
	glGenBuffers(1, &index_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	num_indices = 3;

#endif
}


void DrawElementsInstance::sendAnotherTriToOpenGL()
{
	if (numTriangles1 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles1 * X_PITCH;
	GLfloat another_tri[] =
	{
		Cur_Tri_X,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X + X_PITCH,1.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X,1.0f,0.0f,
		1.0f,0.0f,0.0f,
	};
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles1 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles1++;
}

extern bool checkShaderStatus(GLuint vertex_shader_id);
extern string readShaderCode(const char* file);


void DrawElementsInstance::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	const char* adapter[1];
	string temp;
	temp = readShaderCode("DrawElementsInstance.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertex_shader_id, 1, adapter, NULL);

	temp = readShaderCode("fragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id, 1, adapter, NULL);

	//compile the shader
	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	//If error takes place in QtGLShaderCode.cpp
	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	program_object_id = glCreateProgram();
	glAttachShader(program_object_id, vertex_shader_id);
	glAttachShader(program_object_id, fragment_shader_id);
	glLinkProgram(program_object_id);
	glUseProgram(program_object_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void DrawElementsInstance::initializeGL()
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}

void DrawElementsInstance::paintGL()
{
	glViewport(0, 0, width(), height());
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glDrawElementsInstanced(GL_TRIANGLES,num_indices,GL_UNSIGNED_SHORT,0,5);
}