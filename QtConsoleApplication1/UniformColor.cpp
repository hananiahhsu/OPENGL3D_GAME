#include<glew.h>//put before MeGLWindow.h,or the error taking place
#include<UniformColor.h>
#include<iostream>
#include <fstream>
#include <glm\glm.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\ShapeGenerator.h"
#include <SOIL.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>

using namespace std;
using glm::vec3;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles_01 = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;


void UniformColor::sendDataToOpenGL()
{
	ShapeData shape_data = ShapeGenerator::MakeTriangles();

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, shape_data.vertexBufferSize(), shape_data.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(1);//
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5


	//glBindVertexArray(0); // Unbind VAO


	//Clear the pointers
	shape_data.UsrClearShapeData();
}


void UniformColor::sendAnotherTriToOpenGL()
{
	if (numTriangles_01 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles_01 * X_PITCH;
	GLfloat another_tri[] =
	{
		Cur_Tri_X,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X + X_PITCH,1.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X,1.0f,0.0f,
		1.0f,0.0f,0.0f,
	};
	//bind the sub data
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles_01 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles_01++;
}


//check the status of shader
extern bool checkShaderStatus(GLuint vertex_shader_id);
//read the glsl file
extern string readShaderCode(const char* file);



void UniformColor::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	//pointer array
	const char* adapter[1];
	string temp;
	temp = readShaderCode("UniformColor_VertexShaderCode.glsl");
	adapter[0] = temp.c_str();//another method to get the shader code
	glShaderSource(vertex_shader_id, 1, adapter, NULL);//

													  
	temp = readShaderCode("UniformColor_FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id, 1, adapter, NULL);

	//compile the shader
	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	//If error takes place in QtGLShaderCode.cpp
	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	//
	program_object_id = glCreateProgram();
	glAttachShader(program_object_id, vertex_shader_id);
	glAttachShader(program_object_id, fragment_shader_id);

	glLinkProgram(program_object_id);
	glUseProgram(program_object_id);

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void UniformColor::initializeGL()
{
	//You must initialize the buffer before using glGenBuffer.
	glewInit();
	//Get the version of shader version
	const GLubyte *shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	std::cout << shaderVersion << std::endl;
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本
	std::cout << OpenGLVersion << std::endl;
	const GLubyte* gluVersion = gluGetString(GLU_VERSION); //返回当前GLU工具库版本
	std::cout << gluVersion << std::endl;
	//const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
	//std::cout << biaoshifu << std::endl;


	//Enable gl depth test
	glEnable(GL_DEPTH_TEST);

	//Send datas to OpenGL
	sendDataToOpenGL();
	//install the shaders(vertex shaders and fragment shaders)
	installShaders();

}

void UniformColor::paintGL()
{
	glViewport(0, 0, width(), height());//Get the width and height of the dialog(window)						
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//Get the uniform color by gl functions
	GLint uniformColor_Location = glGetUniformLocation(program_object_id,"uniformColor");
	GLint yFlipUniformLocation = glGetUniformLocation(program_object_id,"yFlip");
	GLint xFlipUniformLocation = glGetUniformLocation(program_object_id, "xFlip");
	GLint zFlipUniformLocation = glGetUniformLocation(program_object_id, "zFlip");

	//The 1st triangle using uniform variable(yFlip,you could also use xFlip or zFlip too)
	vec3 uniColor(0.3f, 0.7f, 1.0f);
	glUniform3fv(uniformColor_Location,1,&uniColor[0]);
	glUniform1f(yFlipUniformLocation,1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

#if 1
	//The 2nd triangle using uniform triangle
	uniColor.r = 0.5f;
	uniColor.b = 0.8f;
	glUniform3fv(uniformColor_Location, 1, &uniColor[0]);
	glUniform1f(yFlipUniformLocation, -1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);


	//The 3rd triangles
	uniColor.r = 0.5f;
	uniColor.g = 0.1f;
	uniColor.b = 0.8f;
	glUniform3fv(uniformColor_Location, 1, &uniColor[0]);
	glUniform1f(xFlipUniformLocation, -1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);
#endif


}