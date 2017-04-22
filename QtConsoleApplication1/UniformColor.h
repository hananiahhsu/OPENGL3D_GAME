#pragma once
#ifndef Uniform_Color
#define Uniform_Color
//#include <QtOpenGL\qtopenglglobal.h>
//#include <QtWidgets\qwidget.h>
//#include <QtOpenGL\QGL>//INCLUDE IN QtOpenGL
//#include <QtWidgets\qopenglwidget.h>
#include<QtOpenGL\QGLshaderProgram>
//#include<QtWidgets\QOpenGLWidget>
#include <QtOpenGL\qglwidget>
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