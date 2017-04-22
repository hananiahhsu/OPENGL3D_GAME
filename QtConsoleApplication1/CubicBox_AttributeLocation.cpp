#include <glew.h>//put before MeGLWindow.h,or the error taking place
#include <CubicBox_AttributeLocation.h>
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\CubeGenerator.h"
#include "glut.h" 
#include "MyCamera.h"

using namespace std;
using glm::vec3;
using glm::mat4;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles_03 = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;

GLuint num_indices_3;//get the number of indices of cubeBox
ShapeData shape_data3;
MyCamera cma(glm::vec3(1.0,0.0,0.0), glm::vec3(0.0f, 1.0f, 0.0f),1,0.5);

//construction function
CubicBox_AttributeLocation::CubicBox_AttributeLocation()
{

}
//Deconstruction function
CubicBox_AttributeLocation::~CubicBox_AttributeLocation()
{
	//Clear the pointers
	shape_data3.UsrClearShapeData();
	//delete program
	glUseProgram(0);
	glDeleteProgram(program_object_id);
}

/*================================================================*\
 2017.4.19-NOTE
 If you don't give the position of "posiiton","vertexColor" in glsl 
 file, then you should bind the position in the following codes;
 \*================================================================*/

void CubicBox_AttributeLocation::sendDataToOpenGL()
{
#if 1
	CubeGenerator cg;
	shape_data3 = cg.MakeCubes();
	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, shape_data3.vertexBufferSize(), shape_data3.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(1);//
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5

    //Here you must generate,bind and bufferdata for element drawing,if not,you cannot draw the cudes at all
	GLuint index_array_buffer_id;
	glGenBuffers(1, &index_array_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_array_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape_data3.indexBufferSize(), shape_data3.indices, GL_STATIC_DRAW);

	//2017.4.19-transform buffer id
	
	GLuint transform_buffer_id;
	glGenBuffers(1,&transform_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER,transform_buffer_id);
    
	mat4 proj_matrix = glm::perspective(80.0f, ((float)width()) / height(), 0.1f, 100.0f);
#if 0
	mat4 full_transform[] =
	{
	   proj_matrix * glm::translate(vec3(-1.0,0.0,-3.0)) * glm::rotate(36.0f,vec3(1.0,0.0,0.0)),
	   proj_matrix * glm::translate(vec3(1.0,0.0,-3.8)) * glm::rotate(120.0f,vec3(0.0,1.0,0.0)),

	};
#endif

#if 1
	//Setup camera
	mat4 full_transform[] =
	{
		proj_matrix * cma.GetWorldToViewMatrix()* glm::translate(vec3(-1.0,0.0,-3.0)) * glm::rotate(36.0f,vec3(1.0,0.0,0.0)),
		proj_matrix * cma.GetWorldToViewMatrix()* glm::translate(vec3(1.0,0.0,-3.8)) * glm::rotate(120.0f,vec3(0.0,1.0,0.0)),

	};
#endif

	glBufferData(GL_ARRAY_BUFFER,sizeof(full_transform), full_transform, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float)*0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float)*4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float)*8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float)*12));
	glEnableVertexAttribArray(2);//
	glEnableVertexAttribArray(3);//
	glEnableVertexAttribArray(4);//
	glEnableVertexAttribArray(5);//

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
#endif

}


void CubicBox_AttributeLocation::sendAnotherTriToOpenGL()
{
	if (numTriangles_03 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles_03 * X_PITCH;
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
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles_03 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles_03++;
}


//check the status of shader
extern bool checkShaderStatus(GLuint vertex_shader_id);
//read the glsl file
extern string readShaderCode(const char* file);




bool CubicBox_AttributeLocation::checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
}

#if 0
bool CubicBox::checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}
#endif

bool CubicBox_AttributeLocation::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}






void CubicBox_AttributeLocation::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	//pointer array
	const char* adapter[1];
	string temp;


#if 1
	temp = readShaderCode("CubicBox_AttributeLocation_VertexShaderCode.glsl");
	adapter[0] = temp.c_str();//another method to get the shader code
	glShaderSource(vertex_shader_id, 1, adapter, NULL);//
#endif

#if 1
	temp = readShaderCode("CubicBox_FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id, 1, adapter, NULL);
#endif
	//compile the shader
	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	//If error takes place in QtGLShaderCode.cpp
	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	program_object_id = glCreateProgram();
	glAttachShader(program_object_id, vertex_shader_id);
	glAttachShader(program_object_id, fragment_shader_id);

	glBindAttribLocation(program_object_id, 0,"position");
	glBindAttribLocation(program_object_id, 1, "vertexColor");
	glBindAttribLocation(program_object_id, 2, "fullTransformMatrix");

	glLinkProgram(program_object_id);
	glUseProgram(program_object_id);

	//check the status of program
	if (!checkProgramStatus(program_object_id))
	{
		return;
	}
	//2017.4.19-get attribute location
	GLint pos_location = glGetAttribLocation(program_object_id,"position");
	GLint vertexColor_location = glGetAttribLocation(program_object_id, "vertexColor");
	GLint fullMatrix_location = glGetAttribLocation(program_object_id, "fullTransformMatrix");

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void CubicBox_AttributeLocation::initializeGL()
{
	//You must initialize the buffer before using glGenBuffer.
	glewInit();
	//Get the version of shader version
	const GLubyte *shaderVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
	//std::cout << (void*)shaderVersion << std::endl;
	std::cout << shaderVersion << std::endl;
	const GLubyte* OpenGLVersion = glGetString(GL_VERSION); //返回当前OpenGL实现的版本
															//std::cout << (void*)OpenGLVersion << std::endl;
	std::cout << OpenGLVersion << std::endl;
	const GLubyte* gluVersion = gluGetString(GLU_VERSION); //返回当前GLU工具库版本
														   //std::cout << (void*)gluVersion << std::endl;
	std::cout << gluVersion << std::endl;
	//const GLubyte* biaoshifu = glGetString(GL_RENDERER); //返回一个渲染器标识符，通常是个硬件平台
	//std::cout << biaoshifu << std::endl;

	//Enable gl depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Send datas to OpenGL
	sendDataToOpenGL();
	//install the shaders(vertex shaders and fragment shaders)
	installShaders();
}

void CubicBox_AttributeLocation::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());//Get the width and height of the dialog(window)

#if 1

	glDrawElementsInstanced(GL_TRIANGLES, shape_data3.num_indices, GL_UNSIGNED_SHORT,0, 2);//successful
																			   
#endif
}




