#pragma once
#include<QtOpenGL\QGLshaderProgram>
#include <QtOpenGL\qglwidget>
#include "loadBMP.h"

class TwoD_texture:public QGLWidget
{
public:
	TwoD_texture() {}
	~TwoD_texture() {}

protected:
	void initializeGL();
	void paintGL();
public:
	void sendDataToOpenGL();
	void sendAnotherTriToOpenGL();
	void installShaders();
public:
	GLuint LoadTexture_01(const std::string& file);
	GLuint LoadTexture(Image * image);
	void LoadTextureMapping();
private:
	GLuint program_object_id;
};




