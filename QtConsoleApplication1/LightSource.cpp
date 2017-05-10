#include <glew.h>//put before MeGLWindow.h,or the error taking place
#include <iostream>
#include <fstream>
#include "LightSource.h"
//#include <Qt\include\Qt3DInput\qmouseevent>
#include <Qt\include\QtGui\QMouseEvent>
#include <Qt\include\QtGui\QKeyEvent>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>

#include "Primitives\Vertex.h"
#include "Primitives\CubeGenerator.h"
#include "glut.h" 
#include "MyCamera.h"
#include "Primitives\ArrowGenerator.h"
#include "Primitives\TeaPotGenerator.h"
#include "Primitives\PlaneGenerator.h"
#include "XuModel.h"
using namespace std;
using glm::vec3;
using glm::mat4;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles_05 = 0;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;


MyCamera cma_02(glm::vec3(1.0, 0.0, 0.0), glm::vec3(0.0f, 1.0f, 0.0f), 1, 0.5);

//==================================================//
ShapeData teapot;
ShapeData plane;

GLuint planeIndexByteOffset;
GLuint teapotIndexByteOffset;

GLuint teapot_num_indices;
GLuint plane_num_indices;

GLuint planeVertexArrayObjectID;
GLuint teapotVertexArrayObjectID;
GLuint passThroughProgramID;
//construction function
LightSource::LightSource(XuModel * Model):theModel(Model)
{

}
//Deconstruction function
LightSource::~LightSource()
{
	//Clear the pointers
	teapot.UsrClearShapeData();
	plane.UsrClearShapeData();
	//delete program
	glUseProgram(0);
	glDeleteProgram(program_object_id);
	glDeleteProgram(passThroughProgramID);
}

/*================================================================*\
2017.4.19-NOTE
If you don't give the position of "posiiton","vertexColor" in glsl
file, then you should bind the position in the following codes;
\*================================================================*/

void LightSource::sendDataToOpenGL()
{
	teapot = TeaPotGenerator::MakeTeaPot();
	plane = PlaneGenerator::MakePlane();

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, 
		         teapot.vertexBufferSize() + teapot.indexBufferSize() + plane.indexBufferSize() + plane.vertexBufferSize(),
		         0, GL_STATIC_DRAW);

	GLsizeiptr currentOffset = 0;

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.vertexBufferSize(), teapot.vertices);
	currentOffset += teapot.vertexBufferSize();
	teapotIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.indexBufferSize(), teapot.indices);
	currentOffset += teapot.indexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.vertexBufferSize(), plane.vertices);
	currentOffset += plane.vertexBufferSize();
	planeIndexByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.indexBufferSize(), plane.indices);
	currentOffset += plane.indexBufferSize();




	plane_num_indices = plane.num_indices;
	teapot_num_indices = teapot.num_indices;

	glGenVertexArrays(1, &teapotVertexArrayObjectID);
	glGenVertexArrays(1, &planeVertexArrayObjectID);


	//teapot
	glBindVertexArray(teapotVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buffer_id);


	//plane
	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	GLuint planeByteOffset = teapot.vertexBufferSize() + teapot.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)planeByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planeByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planeByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buffer_id);


}


void LightSource::sendAnotherTriToOpenGL()
{
	if (numTriangles_05 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles_05 * X_PITCH;
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
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles_05 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles_05++;
}


//check the status of shader
extern bool checkShaderStatus(GLuint vertex_shader_id);
//read the glsl file
extern string readShaderCode(const char* file);




bool LightSource::checkStatus(
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


bool LightSource::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}



void LightSource::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
	//pointer array
	const char* adapter[1];
	string temp;

	temp = readShaderCode("LightSource_VertexShaderCode.glsl");
	adapter[0] = temp.c_str();//another method to get the shader code
	glShaderSource(vertex_shader_id, 1, adapter, NULL);//
	temp = readShaderCode("LightSource_FragmentShaderCode.glsl");
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
	//check the status of program
	if (!checkProgramStatus(program_object_id))
	{
		return;
	}

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

//////////////////////////////////////////////////////////////////////////
	vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	temp = readShaderCode("LightSource_VertexPassthroughCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertex_shader_id, 1, adapter, 0);
	temp = readShaderCode("LightSource_FragmentPassthroughCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id, 1, adapter, 0);

	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	passThroughProgramID = glCreateProgram();
	glAttachShader(passThroughProgramID, vertex_shader_id);
	glAttachShader(passThroughProgramID, fragment_shader_id);

	glLinkProgram(passThroughProgramID);

	if (!checkProgramStatus(passThroughProgramID))
		return;

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void LightSource::initializeGL()
{
	//2017.4.23
	setMinimumSize(800,600);
	setMouseTracking(true);
	glewInit();
	//Enable gl depth test
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	//Send datas to OpenGL
	sendDataToOpenGL();
	//install the shaders(vertex shaders and fragment shaders)
	installShaders();
}

void LightSource::paintGL()
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	glm::vec3 lightPositionWorld = theModel->lightPosition;

	mat4 modelToProjectionMatrix;
	mat4 viewToProjectionMatrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 20.0f);
	mat4 worldToViewMatrix = cma_02.GetWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	GLuint fullTransformationUniformLocation;
	GLuint modelToWorldMatrixUniformLocation;

	glUseProgram(program_object_id);
	GLint ambientLightUniformLocation = glGetUniformLocation(program_object_id, "ambientLight");
	glm::vec4 ambientLight(0.05f, 0.05f, 0.05f, 1.0f);
	glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	GLint eyePositionWorldUniformLocation = glGetUniformLocation(program_object_id, "eyePositionWorld");
	glm::vec3 eyePosition = cma_02.getPosition();
	glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePosition[0]);
	GLint lightPositionUniformLocation = glGetUniformLocation(program_object_id, "lightPositionWorld");
	glUniform3fv(lightPositionUniformLocation, 1, &lightPositionWorld[0]);

	fullTransformationUniformLocation = glGetUniformLocation(program_object_id, "modelToProjectionMatrix");
	modelToWorldMatrixUniformLocation = glGetUniformLocation(program_object_id, "modelToWorldMatrix");


	// Teapot
	glBindVertexArray(teapotVertexArrayObjectID);
	glm::mat4 teapotModelToWorldMatrix =
		glm::translate(vec3(-3.0f, 0.0f, -2.0f)) *
		glm::rotate(-45.0f, vec3(0.0f, 1.0f, 0.0f)) *
		glm::rotate(-50.0f, vec3(1.0f, 0.0f, 0.0f)) *
		glm::scale(vec3(0.5f, 0.5f, 0.5f));
	modelToProjectionMatrix = worldToProjectionMatrix * teapotModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&teapotModelToWorldMatrix[0][0]);
	//glDrawElements(GL_TRIANGLES, teapot.num_indices, GL_UNSIGNED_SHORT, (void*)teapotIndexByteOffset);//(void*)teapotIndexByteOffset


	// Plane
	glBindVertexArray(planeVertexArrayObjectID);
	mat4 planeModelToWorldMatrix;
	modelToProjectionMatrix = worldToProjectionMatrix * planeModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldMatrixUniformLocation, 1, GL_FALSE,
		&planeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES,plane_num_indices, GL_UNSIGNED_SHORT, (void*)0);//(void*)planeIndexByteOffset


}

//The name of function must be mouseMoveEvent()-rewrite
void LightSource::mouseMoveEvent(QMouseEvent *me)
{
	//2017.4.23
	setFocus();
	//update the value of ViewDirection
	//cma_02.mouseUpdate(glm::vec2(me->x(), me->y()));
	cma_02.ProcessMouseMovement(me->x(),me->y(),true);
	repaint();
}

void LightSource::keyPressEvent(QKeyEvent *key)
{
	switch (key->key())
	{
	case Qt::Key::Key_W:
		cma_02.moveForward();
		break;
	case Qt::Key::Key_S:
		cma_02.moveBackward();
		break;
	case Qt::Key::Key_A:
		cma_02.StrafeLeft();
		break;
	case Qt::Key::Key_D:
		cma_02.StrafeRight();
		break;
	case Qt::Key::Key_R:
		cma_02.moveUp();
		break;
	case Qt::Key::Key_F:
		cma_02.moveDown();
		break;
	default:
		break;
	}
	repaint();
}



