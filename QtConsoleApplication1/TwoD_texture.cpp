#include <glew.h>//put before MeGLWindow.h,or the error taking place
#include <TwoD_texture.h>
#include <iostream>
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
GLuint numTriangles_08 = 0;

const GLuint NUM_VERTICES_PER_TRI = 3;
const GLuint NUM_FLOATS_PER_VERTICE = 6;
const GLuint TRI_BYTE_SIZE = NUM_VERTICES_PER_TRI * NUM_FLOATS_PER_VERTICE * sizeof(GLfloat);
const GLuint MAX_TRIS = 20;

GLuint texture1;
GLuint texture2;

GLuint TwoD_texture::LoadTexture(Image * image)
{
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,       //Always GL_TEXTURE_2D
		0,                            //0 for now
		GL_RGB,                       //Format OpenGL uses for image
		image->width, image->height,  //Width and height
		0,                            //The border of the image
		GL_RGB, //GL_RGB, because pixels are stored in RGB format
		GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
						  //as unsigned numbers
		image->pixels);   //The actual pixel data
	return textureId; //Returns the id of the texture
}
void TwoD_texture::LoadTextureMapping()
{
	Image* image = loadBMP("E:/X_HSU/201703/GraphicsApplication/bmp.bmp");
	texture1 = LoadTexture(image);
	delete image;
}

GLuint TwoD_texture::LoadTexture_01(const std::string& file)
{
	GLuint textureID = SOIL_load_OGL_texture(file.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

void TwoD_texture::sendDataToOpenGL()
{
	//ShapeData shape_data = ShapeGenerator::MakeTriangles();
	TextureData tex_data = ShapeGenerator::MakeTextures();


	GLuint vertex_buffer_id;
	glGenBuffers(1, &vertex_buffer_id);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_id);
	glBufferData(GL_ARRAY_BUFFER, tex_data.vertexBufferSize(), tex_data.vertices, GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);//from vertexed[],you can see that the stride of potion is sizeof(float)*5
	glEnableVertexAttribArray(0);//

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (char*)(sizeof(GLfloat) * 3));//from vertexed[],you can see that the stride of color is also sizeof(float)*5
	glEnableVertexAttribArray(1);//
																									   // TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
    
	texture1 = LoadTexture_01("E:/X_HSU/201703/GraphicsApplication/bmp.bmp");

#if 0
	// Load and create a texture
	// Texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1); // All upcoming GL_TEXTURE_2D operations now have effect on our texture object

											// Bind Textures using texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glUniform1i(glGetUniformLocation(program_object_id, "ourTexture1"), 0);

	// Load, create texture and generate mipmaps
	int width = 0, height = 0;
	unsigned char* image = SOIL_load_image("E:/X_HSU/201703/GraphicsApplication/texture.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);

	// Set our texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);// Set texture wrapping to GL_REPEAT
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Unbind texture when done, so we won't accidentily mess up our texture.
	glBindTexture(GL_TEXTURE_2D, 0);
#endif


#if 0
	glGenTextures(1, &texture1);

	/* load an image file directly as a new OpenGL texture */
	texture1 = SOIL_load_OGL_texture
	(
		"E:/X_HSU/201703/GraphicsApplication/texture.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
	);

	if (texture1 == 0)
		return;

	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


#endif
	//glBindVertexArray(0); // Unbind VAO

	//Clear the pointers
	tex_data.UsrClearShapeData();
}


void TwoD_texture::sendAnotherTriToOpenGL()
{
	if (numTriangles_08 == MAX_TRIS)
		return;
	//counter clock-wise
	const GLfloat Cur_Tri_X = -1 + numTriangles_08 * X_PITCH;
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
	glBufferSubData(GL_ARRAY_BUFFER, numTriangles_08 * TRI_BYTE_SIZE, TRI_BYTE_SIZE, another_tri);
	numTriangles_08++;
}


//check the status of shader
extern bool checkShaderStatus(GLuint vertex_shader_id);
//read the glsl file
extern string readShaderCode(const char* file);



void TwoD_texture::installShaders()
{
	//create a vertex opengl object(VSO)
	GLuint vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

	//pointer array
	const char* adapter[1];
	string temp;
	temp = readShaderCode("TwoD_texture_VertexShaderCode.glsl");
	adapter[0] = temp.c_str();//another method to get the shader code
	glShaderSource(vertex_shader_id, 1, adapter, NULL);//

	temp = readShaderCode("TwoD_texture_FragmentShaderCode.glsl");
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


void TwoD_texture::initializeGL()
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

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	//install the shaders(vertex shaders and fragment shaders)
	installShaders();


}

void TwoD_texture::paintGL()
{
	glViewport(0, 0, width(), height());//Get the width and height of the dialog(window)

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, 3);

#if 0
	//Get the uniform color by gl functions
	GLint uniformColor_Location = glGetUniformLocation(program_object_id, "uniformColor");
	GLint yFlipUniformLocation = glGetUniformLocation(program_object_id, "yFlip");
	GLint xFlipUniformLocation = glGetUniformLocation(program_object_id, "xFlip");
	GLint zFlipUniformLocation = glGetUniformLocation(program_object_id, "zFlip");

	//The 1st triangle using uniform variable(yFlip,you could also use xFlip or zFlip too)
	vec3 uniColor(0.3f, 0.7f, 1.0f);
	glUniform3fv(uniformColor_Location, 1, &uniColor[0]);
	glUniform1f(yFlipUniformLocation, 1.0f);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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