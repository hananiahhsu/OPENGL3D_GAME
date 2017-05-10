#pragma once
#ifndef Uniform_Color
#define Uniform_Color
#include<QtOpenGL\QGLshaderProgram>
#include <QtOpenGL\qglwidget>
#include "loadBMP.h"

class UniformColor :public QGLWidget
{
public:
	UniformColor() {}
	~UniformColor() {}

protected:
	void initializeGL();
	void paintGL();
public:
	void sendDataToOpenGL();
	void sendAnotherTriToOpenGL();
	void installShaders();
private:
	GLuint program_object_id;
};



#endif