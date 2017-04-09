#include<glew.h>//put before MeGLWindow.h,or the error taking place
#include<MeGLWindow.h>
#include<iostream>
#include <fstream>
#include <glm\glm.hpp>
#include "Primitives\Vertex.h"
#include "Primitives\ShapeGenerator.h"
using namespace std;
#if 0
//GL type
C Type	Bitdepth	Description	Common Enum
GLboolean	        1 + A boolean value, either GL_TRUE or GL_FALSE
GLbyte	8	        Signed, 2's complement binary integer	GL_BYTE
GLubyte	8	        Unsigned binary integer	GL_UNSIGNED_BYTE
GLshort	16	        Signed, 2's complement binary integer	GL_SHORT
GLushort	16	    Unsigned binary integer	GL_UNSIGNED_SHORT
GLint	32	        Signed, 2's complement binary integer	GL_INT
GLuint	32	        Unsigned binary integer	GL_UNSIGNED_INT
GLfixed	32	        Signed, 2's complement 16.16 integer	GL_FIXED
GLint64	64	        Signed, 2's complement binary integer	
GLuint64 64	        Unsigned binary integer
GLsizei	32	        A non - negative binary integer, for sizes.
GLenum	32	        An OpenGL enumerator value
GLintptr	  ptrbits ? 1	Signed, 2's complement binary integer	
GLsizeiptr	ptrbits ? 1	Non - negative binary integer size, for pointer offsets and ranges
GLsync	ptrbits ? 1	Sync Object handle
GLbitfield	32	A bitfield value
GLhalf	16	An IEEE - 754 floating - point value	GL_HALF_FLOAT
GLfloat	32	An IEEE - 754 floating - point value	GL_FLOAT
GLclampf	32	An IEEE - 754 floating - point value, clamped to the range[0, 1]
GLdouble	64	An IEEE - 754 floating - point value	GL_DOUBLE
GLclampd	64	An IEEE - 754 floating - point value, clamped to the range[0, 1]


#endif


extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

//pitch for X-axis moving
const GLfloat X_PITCH = 0.1f;
const GLfloat Y_PITCH = 0.1f;
GLuint numTriangles = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;


void MeGLWindow::sendDataToOpenGL()
{
	//a triangle vertextes-1-dimensional array
#if 0
	GLfloat vertexes[]
	{
		0.0f,+1.0f,
		-1.0f,-1.0f,
		+1.0f,-1.0f,
	};
#endif

#if 0
	//Drawing 4 triangles on the dialog
	//counter-clockwise direction of pnts location
	GLfloat vertexes[]
	{
		0.0f,+0.0f,
		1.0f,-1.0f,
		1.0f,1.0f,

		0.0f,+0.0f,//redundant point
		-1.0f,1.0f,
		-1.0f,-1.0f,
	};
#endif

#if 0
	//The array is for GLSL compiling shaders
	//counter-clockwise direction of pnts location
	//This structure contains 5 points of two triangles for we remove the redundant point(0.0,0.0,0.0.) 
	//which is the common point of the 2 triangles
	GLfloat vertexes[]
	{
		0.0f,+0.0f,//-0(position)
		0.0f,1.0f,1.0f,//-0(color-red)
		1.0f,1.0f,//-1(position)
		0.0f,1.0f,1.0f,//-0(color-green)
		-1.0f,1.0f,//-2(position)
		0.0f,1.0f,0.0f,//-0(color-blue)

		-1.0f,-1.0f,//-3(position)
		0.0f,1.0f,0.0f,//-0(color)
		1.0f,-1.0f,//-4(position)
		0.0f,1.0f,0.0f,//-0(color)
	};
#endif



#if 0
	//The vertexes is for vertex attribute triangle interpolation
	//Blend the RGB together
	GLfloat vertexes[]
	{
		0.0f,1.0f,
		1.0f,0.0f,0.0f,
		-1.0f,-1.0f,
		0.0f,1.0f,0.0f,
		1.0f,-1.0f,
		0.0f,0.0f,1.0f
	};

#endif


#if 0
    //The array is for lecture18--fragment and pixel
	//red and blue triangles
	GLfloat vertexes[]
	{
		-1.0f,-1.0f,//-0(position)
		1.0f,0.0f,0.0f,//-0(color-red)
		0.0f,1.0f,//-1(position)
		1.0f,0.0f,0.0f,//-0(color-green)
		1.0f,-1.0f,//-2(position)
		1.0f,0.0f,0.0f,//-0(color-blue)

		-1.0f,1.0f,//-3(position)
		0.0f,0.0f,1.0f,//-0(color)
		0.0f,-1.0f,//-4(position)
		0.0f,0.0f,1.0f,//-0(color)
		1.0f,1.0f,
		0.0f,0.0f,1.0f,
	};
#endif


#if 0
	//The array is for lecture20-GLenable depth
	//red and blue triangles
	//Use the Z-AXIS value as the depth
	GLfloat RED_Z_DEPTH = 0.5f;
	GLfloat BLUE_Z_DEPTH = -0.5f;
	GLfloat vertexes[]
	{
		-1.0f,-1.0f,RED_Z_DEPTH,//-0(position)
		1.0f,0.0f,0.0f,//-0(color-red)
		0.0f,1.0f,RED_Z_DEPTH,//-1(position)
		1.0f,0.0f,0.0f,//-0(color-green)
		1.0f,-1.0f,RED_Z_DEPTH,//-2(position)
		1.0f,0.0f,0.0f,//-0(color-blue)

		-1.0f,1.0f,BLUE_Z_DEPTH,//-3(position)
		0.0f,0.0f,1.0f,//-0(color)
		0.0f,-1.0f,BLUE_Z_DEPTH,//-4(position)
		0.0f,0.0f,1.0f,//-0(color)
		1.0f,1.0f,BLUE_Z_DEPTH,
		0.0f,0.0f,1.0f,
	};

	//Buffer object-BINDING gl_object to GL_ARRAY_BUFFER
	//gl_element_array_buffer :
	//gl_array_buffer:
	//Stride:the gap space between postion address or color address
	//Color mode:RGBA
	//glVertexAttribPointer()-the 4th parameter is for the starting address of color 
	//vertex attribute--> vertex shader:(position,custom data-->fragment shader-->RGB)
	//Segment shader:

	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexes), vertexes, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);//
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(1);//
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5

																									   //GLushort indices[] = { 0,1,2,0,3,4 };//why use the GLushort?
	GLushort indices[] = { 3,4,5,0,1,2 };//for lecture 18-fragment and pixel
	GLuint index_vertex_id;
	glGenBuffers(1, &index_vertex_id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vertex_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

#endif

#if 0
//This section realize the function of drawing saw-like triangles
GLuint vertex_buffer_id;
glGenBuffers(1, &vertex_buffer_id);
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
glBufferData(GL_ARRAY_BUFFER,MAX_TRIS * TRI_BYTE_SIZE, NULL, GL_STATIC_DRAW);//_nullptr, or 0 is okay too

glEnableVertexAttribArray(0);//
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
glEnableVertexAttribArray(1);//
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5
#endif



#if 1
//GLM
//This section realize the vertex data structure using glm
//2017.4.7-move myTri[] to shapeData.cpp
/*
Vertex myTri[] =
{
	glm::vec3(0.0f,1.0f,0.0f),
	glm::vec3(1.0f,0.0f,0.0f),

	glm::vec3(-1.0f,-1.0f,0.0f),
	glm::vec3(0.0f,1.0f,0.0f),

	glm::vec3(1.0f,-1.0f,0.0f),
	glm::vec3(0.0f,0.0f,1.0f),
};
*/
ShapeData shape_data = ShapeGenerator::MakeTriangles();
GLuint vertex_buffer_id;
glGenBuffers(1, &vertex_buffer_id);
glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
glBufferData(GL_ARRAY_BUFFER,shape_data.vertexBufferSize(), shape_data.vertices, GL_STATIC_DRAW);

glEnableVertexAttribArray(0);//
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
glEnableVertexAttribArray(1);//
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5
#endif



}


void MeGLWindow::sendAnotherTriToOpenGL()
{
	if (numTriangles == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles * X_PITCH;
	GLfloat another_tri[] =
	{
		Cur_Tri_X,0.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X+X_PITCH,1.0f,0.0f,
		1.0f,0.0f,0.0f,

		Cur_Tri_X,1.0f,0.0f,
		1.0f,0.0f,0.0f,
	};

	//bind the sub data
	glBufferSubData(GL_ARRAY_BUFFER,numTriangles * TRI_BYTE_SIZE,TRI_BYTE_SIZE,another_tri);
	numTriangles++;
}





//check the status of shader
bool checkShaderStatus(GLuint vertex_shader_id)
{
	//The 3rd param could be integer or a vector
	GLint compile_status[10], compileStatus;
	glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &compileStatus);
	if (GL_TRUE != compileStatus)
	{
		GLint infoLogLength;
		glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar *buffer = new GLchar[infoLogLength];
		GLsizei buffer_size;
		glGetShaderInfoLog(vertex_shader_id, infoLogLength, &buffer_size, buffer);

		std::cout << buffer << std::endl;

		delete[] buffer;
		return false;
	}
	return true;
}


//read the glsl file
string readShaderCode(const char* file)
{
	ifstream glsl_file(file);
	if (!glsl_file.good())
	{
		std::cout << "Glsl file failed to load..." << file <<std::endl;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(glsl_file),
		std::istreambuf_iterator<char>());

}





void MeGLWindow::installShaders()
{
    //create a vertex opengl object(VSO)
	GLuint vertex_shader_id =  glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	//pointer array
	const char* adapter[1];
	//adapter[0] = vertexShaderCode;
	string temp;
	temp = readShaderCode("vertexShaderCode.glsl");
	adapter[0] = temp.c_str();//another method to get the shader code
	glShaderSource(vertex_shader_id,1,adapter,NULL);//

	//adapter[0] = fragmentShaderCode;
	temp = readShaderCode("fragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragment_shader_id,1,adapter,NULL);

	//compile the shader
	glCompileShader(vertex_shader_id);
	glCompileShader(fragment_shader_id);

	//If error takes place in QtGLShaderCode.cpp
	if (!checkShaderStatus(vertex_shader_id) || !checkShaderStatus(fragment_shader_id))
		return;

	//
	program_object_id = glCreateProgram();
	glAttachShader(program_object_id,vertex_shader_id);
	glAttachShader(program_object_id,fragment_shader_id);
	glLinkProgram(program_object_id);
	glUseProgram(program_object_id);

	//Delete the shaders as the program has them now
	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);
}


void MeGLWindow::initializeGL()
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

void MeGLWindow::paintGL()
{
#if 0
	//Set the background color--to red
	glClearColor(1,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT);
#endif
	glViewport(0,0,width(),height());//Get the width and height of the dialog(window)
	//Notes:The following commented lines are several steps of trying to realize different functions
	//glDrawArrays(GL_TRIANGLES,0,3);//Draw 1 triangle on the drialog by the vertex
	//glDrawArrays(GL_TRIANGLES,0,6);//Draw 2 triangle on the dialog by the vertex


	//glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//Note:The function is used for indices only
	//glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_SHORT,0);//commented for lecture 21-drawing any types of triangles,eg saw-like
	glDrawArrays(GL_TRIANGLES, 0, 3);


#if 0
	//Draw many saw-like triangles
	//send another triangles to OpenGL 
	sendAnotherTriToOpenGL();
	//To draw many specific triangles
	//glDrawArrays(GL_TRIANGLES,0,numTriangles * NUM_VERTICES_PER_TRI);
	glDrawArrays(GL_TRIANGLES, (numTriangles-1)*NUM_VERTICES_PER_TRI,NUM_VERTICES_PER_TRI);

#endif
}  