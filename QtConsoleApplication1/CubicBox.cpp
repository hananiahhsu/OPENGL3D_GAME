#include <glew.h>//put before MeGLWindow.h,or the error taking place
#include <CubicBox.h>
#include <iostream>
#include <fstream>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\CubeGenerator.h"
#include "glut.h" 

using namespace std;
using glm::vec3;
using glm::mat4;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles_02 = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;

GLuint num_indices;//get the number of indices of cubeBox
ShapeData shape_data;
//construction function
CubicBox::CubicBox()
{

}
//Deconstruction function
CubicBox::~CubicBox()
{
	//Clear the pointers
	shape_data.UsrClearShapeData();
	//delete program
	glUseProgram(0);
	glDeleteProgram(program_object_id);
}




void CubicBox::sendDataToOpenGL()
{
#if 1
	CubeGenerator cg;
	shape_data = cg.MakeCubes();
	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, shape_data.vertexBufferSize(), shape_data.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(1);//
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5

	//Here you must generate,bind and bufferdata for element drawing,if not,you cannot draw the cudes at all
	GLuint index_array_buffer_id;
	glGenBuffers(1,&index_array_buffer_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,index_array_buffer_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,shape_data.indexBufferSize(),shape_data.indices,GL_STATIC_DRAW);



#endif

}


void CubicBox::sendAnotherTriToOpenGL()
{
	if (numTriangles_02 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles_02 * X_PITCH;
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
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles_02 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles_02++;
}


//check the status of shader
extern bool checkShaderStatus(GLuint vertex_shader_id);
//read the glsl file
extern string readShaderCode(const char* file);




bool CubicBox::checkStatus(
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

bool CubicBox::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}






void CubicBox::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	//pointer array
	const char* adapter[1];
	string temp;

#if 0 
	temp = readShaderCode("CubicBox_VertexShaderCode.glsl");
#endif

#if 1
	temp = readShaderCode("simple_rotation_VertexShaderCode.glsl");
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

	//
	program_object_id = glCreateProgram();
	glAttachShader(program_object_id, vertex_shader_id);
	glAttachShader(program_object_id, fragment_shader_id);
	glLinkProgram(program_object_id);
	glUseProgram(program_object_id);

	//check the status of program
	if (!checkProgramStatus(program_object_id))
	{
		return;
	}
	//2017.4.19-get attribute location



	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void CubicBox::initializeGL()
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

void CubicBox::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());//Get the width and height of the dialog(window)

	//Get the uniform color by gl functions
	//GLint uniformColor_Location = glGetUniformLocation(program_object_id, "uniformColor");

#if 0
	//PLEASE change the glsl file first of all
	mat4 mdlTrfMatrix = glm::translate(mat4(),vec3(0.0f,0.0f,-3.0f));
	mat4 projMatrix = glm::perspective(60.0f,(float)width()/height(),0.1f,10.0f);

	//Here send the data to glsl files
	GLint mdlTrfMatrix_Location = glGetUniformLocation(program_object_id,"mdlTrfMatrix");
	GLint projMatrix_Location = glGetUniformLocation(program_object_id, "projMatrix");

	glUniformMatrix4fv(mdlTrfMatrix_Location, 1, GL_FALSE, &mdlTrfMatrix[0][0]);
	glUniformMatrix4fv(projMatrix_Location, 1, GL_FALSE, &projMatrix[0][0]);
#endif 


#if 0
	mat4 translation_matrix = glm::translate(mat4(), vec3(0.0f, 0.0f, -3.0f));
	mat4 rotation_matrix = glm::rotate(mat4(),54.0f,vec3(1.0f,0.5f,0.0f));
	mat4 proj_matrix = glm::perspective(80.0f, ((float)width()) / height(), 0.1f, 100.0f);
	
	mat4 full_matrix = proj_matrix * translation_matrix * rotation_matrix ;
	//Here send the data to glsl files
	GLint fullMatrix_Location = glGetUniformLocation(program_object_id, "fullTrfMatrix");
	glUniformMatrix4fv(fullMatrix_Location,1,GL_FALSE,&full_matrix[0][0]);

#endif 

#if 0
	//2017.4.18
	//Combine the multiplication of matrix
	mat4 proj_matrix = glm::perspective(80.0f, ((float)width()) / height(), 0.1f, 100.0f);
	mat4 proj_translation_matrix = glm::translate(proj_matrix, vec3(0.0f, 0.0f, -3.0f));
	mat4 full_matrix = glm::rotate(proj_translation_matrix, 54.0f, vec3(1.0f, 0.5f, 0.f));

	//Here send the data to glsl files
	GLint fullMatrix_Location = glGetUniformLocation(program_object_id, "fullTrfMatrix");
	glUniformMatrix4fv(fullMatrix_Location, 1, GL_FALSE, &full_matrix[0][0]);

#endif 

#if 0
	//The order of matrix multiplication matters much
	mat4 translation_matrix = glm::translate(mat4(), vec3(0.0f, 0.0f, -3.0f));
	mat4 rotation_matrix = glm::rotate(mat4(), 54.0f, vec3(1.0f, 0.5f, 0.8f));
	mat4 proj_matrix = glm::perspective(80.0f, ((float)width()) / height(), 0.1f, 100.0f);

	mat4 full_matrix1 = proj_matrix * translation_matrix * rotation_matrix;
	//mat4 full_matrix2 = translation_matrix * proj_matrix * rotation_matrix;
	//mat4 full_matrix3 = rotation_matrix * translation_matrix * proj_matrix ;

	//Here send the data to glsl files
	GLint fullMatrix_Location = glGetUniformLocation(program_object_id, "fullTrfMatrix");
	glUniformMatrix4fv(fullMatrix_Location, 1, GL_FALSE, &full_matrix1[0][0]);

#endif 


#if 1
	//instancing of 2 or more cubes
	mat4 full_matrix;
	mat4 proj_matrix = glm::perspective(80.0f, ((float)width()) / height(), 0.1f, 100.0f);
	//Combine the multiplication of matrix
	//--Cube 1
	mat4 translation_matrix = glm::translate(vec3(-2.0f, 1.0f, -3.0f));
	mat4 rotate_matrix = glm::rotate(54.0f, vec3(1.0f, 0.5f, 0.f));
	full_matrix = proj_matrix * translation_matrix * rotate_matrix;
	//Here send the data to glsl files
	GLint fullMatrix_Location = glGetUniformLocation(program_object_id, "fullTrfMatrix");
	glUniformMatrix4fv(fullMatrix_Location, 1, GL_FALSE, &full_matrix[0][0]);
	glDrawElements(GL_TRIANGLES, shape_data.num_indices, GL_UNSIGNED_SHORT, 0);//successful

	//--Cube 2
	translation_matrix = glm::translate(vec3(1.0f, 0.0f, -2.0f));
	rotate_matrix = glm::rotate(70.0f, vec3(1.0f, 0.5f, 0.f));
	full_matrix = proj_matrix * translation_matrix * rotate_matrix;

	//Here send the data to glsl files
	fullMatrix_Location = glGetUniformLocation(program_object_id, "fullTrfMatrix");
	glUniformMatrix4fv(fullMatrix_Location, 1, GL_FALSE, &full_matrix[0][0]);
	glDrawElements(GL_TRIANGLES, shape_data.num_indices, GL_UNSIGNED_SHORT, 0);//successful



#endif






#if 0
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT,shape_data.indices);//failed for the second
	glDrawElements(GL_TRIANGLES, shape_data.num_indices, GL_UNSIGNED_SHORT, 0);//successful
	//glDrawArrays(GL_TRIANGLES, 5, shape_data.num_vertices);
#endif
}




/*======================================================================================*\
  //2017.4.17
  The traditional way of rendering

\*=======================================================================================*/

void CubicBox::main(int argc, char** argv)
{
	CubicBox cb;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);

	init();
	glutDisplayFunc(cb.display);
	glutMainLoop();

	return;
}


 void CubicBox::init(void)
{
	 //Enable gl depth test
	 glEnable(GL_DEPTH_TEST);


}
 void CubicBox::display(void)
{
	 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


}
 void CubicBox::reshape(int w, int h)
{

}
 void CubicBox::keyboard(unsigned char key, int x, int y)
{

}
 void CubicBox::spinDisplay(void)
{

}